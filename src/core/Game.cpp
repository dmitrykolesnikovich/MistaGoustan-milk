#include "Game.h"

#include <iostream>

#include "SDL.h"
#include "SDL_events.h"
#include "SDL_image.h"

#include "../utilities/Input.h"
#include "../utilities/Timer.h"

#include "../luahandles/LuaHandleRegistry.h"

Game::Game()
	: sceneLoader_(*this)
{
}

Game::Game(const GameRunParameters& runParams)
	: window_(runParams.title, runParams.width, runParams.height, runParams.virtualWidth, runParams.virtualHeight, runParams.fullscreen)
	, sceneLoader_(*this)
	, resourceManager_(runParams.resourceRootDir)
	, sceneToLoad_(runParams.entryScene)
{
}

int Game::run()
{
	// Shit.. if SDL fails, then you can consider the game to be MILK_FAIL'd, beitch.
	if (!initSDLSubsystems() || !initGameWindow())
		return MILK_FAIL;

	initLua();
	initGameSubsystems();

	isRunning_ = true;

	std::cout << "Game started" << std::endl;
	std::cout << "//////////////////" << std::endl;

	const int SCREEN_FPS = 60;
	const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

	Timer fpsTimer;
	Timer frameCapTimer;

	int countedFrames = 0;

	fpsTimer.start();

	try 
	{
		while (isRunning_)
		{
			frameCapTimer.start();

			float averageFps = countedFrames / (fpsTimer.getTicks() / 1000.f);
			if (averageFps > 2000000)
				averageFps = 0;

			handleEvents();
			update();
			render();

			countedFrames++;

			int frameTicks = frameCapTimer.getTicks();
			if (frameTicks < SCREEN_TICKS_PER_FRAME)
				SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}
	}
	catch(const std::exception& e)
	{
		std::cout << "Fatal error occurred: " << e.what() << std::endl;

		shutDown();

		return MILK_FAIL;
	}

	shutDown();

	return MILK_SUCCESS;
}

void Game::handleEvents()
{
	SDL_Event e;

	while (SDL_PollEvent(&e)) 
	{
		switch (e.type) 
		{
			case SDL_QUIT:
				isRunning_ = false;
				break;
			case SDL_KEYUP:
				if (e.key.keysym.sym == SDLK_ESCAPE)
					isRunning_ = false;
				break;
			default:
				break;
		}

		systemManager_.handleInputEvent(e);
	}

	// It is important that this is caused AFTER polling all events.
	// SDL_Poll events internal updates SDL key states, which is what input uses.
	Input::updateKeyboardState();

	while (!eventQueue_.empty())
	{
		auto e = eventQueue_.popEvent();
		systemManager_.handleGameEvent(*e);
	}
}

void Game::update()
{
	if (!sceneToLoad_.empty()) 
	{
		if (currentScene_ != nullptr) 
		{
			currentScene_->unload();
			currentScene_.release();

			resourceManager_.freeResources();
		}

		currentScene_ = sceneLoader_.load(sceneToLoad_);

		sceneToLoad_.clear();
	}

	if (currentScene_ != nullptr) 
	{
		currentScene_->update();
		
		systemManager_.update();
	}
}

void Game::render()
{
	SDL_RenderClear(window_.sdlRenderer());

	if (currentScene_ != nullptr) 	
		systemManager_.render(*currentScene_);	

	SDL_RenderPresent(window_.sdlRenderer());
}

void Game::shutDown()
{
	std::cout << "Freeing Resources" << std::endl;
	std::cout << "//////////////////" << std::endl;

	resourceManager_.freeResources();

	systemManager_.unload();

	window_.freeSDLResources();

	IMG_Quit();
	SDL_Quit();

	std::cout << "Game shutting down" << std::endl;
	std::cout << "//////////////////" << std::endl;
}

Window& Game::window()
{
	return window_;
}

ResourceManager& Game::resourceManager()
{
	return resourceManager_;
}

ActorEventQueue& Game::eventQueue()
{
	return eventQueue_;
}

void Game::loadScene(const std::string& name)
{
	sceneToLoad_ = name;
}

bool Game::initSDLSubsystems()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)
	{
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return false;
	}

	int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	if ((IMG_Init(imgFlags) & imgFlags) != imgFlags)
	{
		SDL_Quit();

		std::cout << "Error initializing SDL_image: " << IMG_GetError() << std::endl;
		return false;
	}

	return true;
}

bool Game::initGameWindow()
{
	if (!window_.initSDLRenderWindow()) 
	{
		IMG_Quit();
		SDL_Quit();

		return false;
	}

	return true;
}

void Game::initLua()
{
	luaState_.open_libraries(sol::lib::base, sol::lib::math, sol::lib::package);

	LuaHandleRegistry::RegisterHandles(luaState_);

	luaState_["game"] = this;
}

void Game::initGameSubsystems()
{
	Input::initialize();

	resourceManager_.init(window_.sdlRenderer());

	SystemManagerParams params = {
		luaState_,
		eventQueue_,
		*window_.sdlRenderer(),
		resourceManager_
	};

	systemManager_.init(params);
}
