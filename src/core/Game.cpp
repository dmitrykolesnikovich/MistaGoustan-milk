#include "Game.h"

#include <iostream>

#include "SDL.h"
#include "SDL_events.h"
#include "SDL_image.h"

#include "../utilities/Input.h"

#include "../luahandles/LuaHandle_Actor.h"

Game::~Game()
{
}

Game& Game::getInstance() 
{
	static Game instance;
	return instance;
}

bool Game::init(const std::string& title, unsigned int width, unsigned int height, bool fullscreen)
{
	// InitSDLSubsystems and initGameWindow both initialize SDL related items.
	if (!initSDLSubsystems() || !initGameWindow(title, width, height, fullscreen))
		return false;

	initLua();
	initGameSubsystems();

	isRunning_ = true;
	
	std::cout << "Game started" << std::endl;
	std::cout << "//////////////////" << std::endl;

	return true;
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
	}

	Input::updateKeyboardState();
}

void Game::update()
{
	if (!sceneToLoad_.empty()) 
	{
		if (currentScene_ != nullptr) 
		{
			currentScene_->unload();
			currentScene_.release();

			resourceManager_.unloadTextures();
		}

		currentScene_ = sceneLoader_.load(sceneToLoad_);

		sceneToLoad_.clear();
	}

	if (currentScene_ != nullptr) 
	{
		currentScene_->update();
		logicSystem_->update();
		physicsSystem_->update();
	}
}

void Game::render()
{
	SDL_RenderClear(window_.sdlRenderer());

	if (currentScene_ != nullptr) 
	{
		renderSystem_->render(currentScene_->getTilemap());
	}

	SDL_RenderPresent(window_.sdlRenderer());
}

bool Game::isRunning() const
{
	return isRunning_;
}

void Game::shutDown()
{
	std::cout << "Freeing Resources" << std::endl;
	std::cout << "//////////////////" << std::endl;

	resourceManager_.freeResources();

	logicSystem_.release();
	physicsSystem_.release();
	renderSystem_.release();

	window_.freeSDLResources();

	IMG_Quit();
	SDL_Quit();

	std::cout << "Game shutting down" << std::endl;
	std::cout << "//////////////////" << std::endl;
}

Window& Game::getWindow()
{
	return window_;
}

ResourceManager& Game::getResourceManager()
{
	return resourceManager_;
}

void Game::loadScene(const std::string& name)
{
	sceneToLoad_ = name;
}

void Game::onActorSpawned(Actor& actor)
{
	logicSystem_->onActorAdded(actor);
	physicsSystem_->onActorAdded(actor);
	renderSystem_->onActorAdded(actor);
}

void Game::onActorDestroyed(Actor& actor)
{
	logicSystem_->onActorDestroyed(actor);
	physicsSystem_->onActorDestroyed(actor);
	renderSystem_->onActorDestroyed(actor);
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

bool Game::initGameWindow(const std::string& title, unsigned int width, unsigned int height, bool fullscreen)
{
	window_ = Window(title, width, height, fullscreen);

	if (!window_.init()) 
	{
		IMG_Quit();
		SDL_Quit();

		return false;
	}

	return true;
}

bool Game::initLua()
{
	luaState_.open_libraries(sol::lib::base, sol::lib::package);

	luaState_.new_usertype<Input>("Input",
		"getKey", &Input::getKey);

	luaState_.new_usertype<LuaHandle_Actor>("actor",
		"move", &LuaHandle_Actor::move);

	luaState_.new_usertype<Vector2d>("Vector2D",
		sol::constructors<Vector2d(), Vector2d(int, int)>(),
		"x", &Vector2d::x,
		"y", &Vector2d::y);

	return true; // try catch for errors?
}

bool Game::initGameSubsystems()
{
	Input::initialize();

	resourceManager_ = ResourceManager(window_.sdlRenderer());

	logicSystem_ = std::unique_ptr<Logic>(new Logic(luaState_));
	physicsSystem_ = std::unique_ptr<Physics>(new Physics());
	renderSystem_ = std::unique_ptr<Renderer>(new Renderer(window_.sdlRenderer(), resourceManager_));

	return true;
}
