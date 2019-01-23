#include "Game.h"

#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "core/Scene.h"

#include "luahandles/LuaHandleRegistry.h"

#ifdef _DEBUG
#include "systems/DebugTools.h"
#endif

#include "systems/EventQueue.h"
#include "utilities/SceneManager.h"
#include "systems/GameEvents.h"
#include "systems/Logic.h"
#include "systems/Physics.h"
#include "systems/Graphics.h"

#include "utilities/Input.h"
#include "utilities/ResourceManager.h"
#include "utilities/SceneLoader.h"
#include "utilities/Timer.h"
#include "utilities/Window.h"

Game::Game() = default;

Game::Game(const std::string& configFile)
	: configFile_(configFile)
{
}

Game::~Game() = default;

int Game::run()
{
	// No game for you.
	if (configFile_.empty())
	{
		std::cout << "Cannot find config file" << std::endl;
		return MILK_FAIL;
	}

	// Init lua first so we can use it to load config file.
    initLua();

	initFromConfig();

	// Shit.. if SDL fails, then you can consider the game to be MILK_FAIL'd, mafk.
	if (!initSDLSubsystems() || !initGameWindow())
		return MILK_FAIL;

	initSubsystems();

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
	while (auto gameEvent = events_->pollEvent())
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
	sceneManager_->update();
	logic_->update();
	physics_->update();
}

void Game::render()
{
	window_->clear();

	// TODO: this is gross. revisit.
	auto scene = sceneManager_->currentScene();
	if (scene != nullptr)
	{
		graphics_->render(*scene);

#ifdef _DEBUG
		debugTools_->render(*scene);
#endif
	}

	window_->present();
}

void Game::shutDown()
{
	std::cout << "Freeing Resources" << std::endl;
	std::cout << "//////////////////" << std::endl;

	sceneManager_->shutDown();
	handleEvents();
	sceneManager_->update();

	resources_->freeResources();

	window_->freeSDLResources();

	IMG_Quit();
	SDL_Quit();

	std::cout << "Game shutting down" << std::endl;
	std::cout << "//////////////////" << std::endl;
}

Window& Game::window() const
{
	return *window_;
}

ResourceManager& Game::resources() const
{
	return *resources_;
}

EventQueue& Game::events() const
{
	return *events_;
}

void Game::loadScene(const std::string& name)
{
	sceneManager_->loadScene(name);
}

void Game::initLua()
{
	luaState_.open_libraries(sol::lib::base, sol::lib::math, sol::lib::package);

	LuaHandleRegistry::RegisterHandles(luaState_);

	luaState_["game"] = this;
}

void Game::initFromConfig()
{
	sol::table config = luaState_.script_file(configFile_);

	std::string title = config["title"];
	int width = config["width"];
	int height = config["height"];
	int vwidth = config["vwidth"];
	int vheight = config["vheight"];
	bool fullscreen = config["fullscreen"];
	std::string resourceRootDir = config["resourceRootDir"];
	std::string entryScene = config["entryScene"];

	window_ = std::make_unique<Window>(title, width, height, vwidth, vheight, fullscreen);

	resources_ = std::make_unique<ResourceManager>(resourceRootDir);

	events_ = std::make_unique<EventQueue>();

    sceneLoader_ = std::make_unique<SceneLoader>(*this);
	sceneManager_ = std::make_unique<SceneManager>(*events_, *sceneLoader_);

	sceneManager_->loadScene(entryScene);
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
	if (!window_->initSDLRenderWindow())
	{
		IMG_Quit();
		SDL_Quit();

		return false;
	}

	return true;
}

void Game::initSubsystems()
{
	Input::initialize();

	resources_->init(window_->sdlRenderer());

#ifdef _DEBUG
	debugTools_ = std::make_unique<DebugTools>(*window_->sdlRenderer());
#endif

	logic_ = std::make_unique<Logic>(luaState_);
	physics_ = std::make_unique<Physics>(*events_);
	graphics_ = std::make_unique<Graphics>(*window_->sdlRenderer(), *resources_);
}
