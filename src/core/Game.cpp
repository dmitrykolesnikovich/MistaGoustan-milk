#include "Game.h"

#include <iostream>

#include "SDL.h"
#include "SDL_events.h"
#include "SDL_image.h"

#include "luahandles/LuaHandleRegistry.h"

#include "systems/GameEvents.h"

#include "utilities/Input.h"
#include "utilities/Timer.h"

// TODO: I need to find a way to remove this stupid ctor, but sol2 needs it for game registration.
Game::Game()
    : sceneLoader_(*this)
    , sceneManager_(events_, sceneLoader_)
{
}

Game::Game(const GameRunParameters& runParams)
	: window_(runParams.title, runParams.width, runParams.height, runParams.virtualWidth, runParams.virtualHeight, runParams.fullscreen)
	, sceneLoader_(*this)
	, resources_(runParams.resourceRootDir)
	, sceneManager_(events_, sceneLoader_)
{
	// TODO: this seems gross to me. revisit plz. An game.init() method might be appropriate here.
    sceneManager_.loadScene(runParams.entryScene);
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
#ifdef _DEBUG
                if (e.key.keysym.sym == SDLK_BACKQUOTE)
                    debugTools_->show = !debugTools_->show;
				break;
#endif
			default:
				break;
		}
	}

	// It is important that this is caused AFTER polling all events.
	// SDL_Poll events internal updates SDL key states, which is what input uses.
	Input::updateKeyboardState();

	// Let systems handle game events enqueued last frame.
	while (auto gameEvent = events_.pollEvent())
	{
		physics_->handleEvent(*gameEvent);
		graphics_->handleEvent(*gameEvent);

#ifdef _DEBUG
        debugTools_->handleEvent(*gameEvent);
#endif

		// It is important to let logic handle it's event last.
		// This is because the previous systems may load resources or init components that a script depends on.
		logic_->handleEvent(*gameEvent);
	}
}

void Game::update()
{
	sceneManager_.update();
	logic_->update();
	physics_->update();
}

void Game::render()
{
	window_.clear();

	// TODO: this is gross. revisit.
	auto scene = sceneManager_.currentScene();
	if (scene != nullptr)
	{
		graphics_->render(*scene);

#ifdef _DEBUG
		debugTools_->render(*scene);
#endif
	}

	window_.present();
}

void Game::shutDown()
{
	std::cout << "Freeing Resources" << std::endl;
	std::cout << "//////////////////" << std::endl;

	sceneManager_.shutDown();
	handleEvents();
	sceneManager_.update();

	resources_.freeResources();

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

ResourceManager& Game::resources()
{
	return resources_;
}

EventQueue& Game::events()
{
	return events_;
}

void Game::loadScene(const std::string& name)
{
	sceneManager_.loadScene(name);
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

	resources_.init(window_.sdlRenderer());

#ifdef _DEBUG
	debugTools_ = std::make_unique<DebugRenderer>(*window_.sdlRenderer());
#endif

	logic_ = std::make_unique<Logic>(luaState_);
	physics_ = std::make_unique<Physics>(events_);
	graphics_ = std::make_unique<Renderer>(*window_.sdlRenderer(), resources_);
}
