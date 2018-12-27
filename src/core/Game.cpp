#include "Game.h"

#include <iostream>

#include <SDL.h>
#include <SDL_events.h>
#include <SDL_image.h>

#include "../utilities/ResourceManager.h"
#include "../utilities/Texture.h"
#include "../math/Vector2d.h"
#include "Scene.h"
#include "../components/Sprite.h"
#include "../components/Velocity.h"
#include "../components/Behavior.h"
#include "../utilities/Input.h"

#include "../externals/sol.hpp"

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
	// Init SDL and initWindow both initialize SDL library stuff.
	// If these two fail, then startup fails.
	if (!initSDL() || !initWindow(title, width, height, fullscreen))
		return false;

	initLua();
	initSystems();

	// Test CODEz
	//////////////////////////////////////////////////
	currentScene_ = std::unique_ptr<Scene>(new Scene(*this));
	auto actor = currentScene_->spawnActor("steve");
	actor->setPosition(50, 50);
	actor->addComponent<Sprite>();
	auto sprite = actor->getComponent<Sprite>();
	sprite->setTextureName("res/steve.png");
	sprite->setSourceRect(0, 0, 64, 64);
	actor->addComponent<Velocity>();
	auto velocity = actor->getComponent<Velocity>();
	actor->addComponent<Behavior>();
	auto behavior = actor->getComponent<Behavior>();
	behavior->setScript("res/player.lua");	
	//////////////////////////////////////////////////

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
	currentScene_->update();
	logicSystem_->update();
	physicsSystem_->update();
}

void Game::render()
{
	SDL_RenderClear(&(window_->getSdlRenderer()));

	renderSystem_->render();

	SDL_RenderPresent(&(window_->getSdlRenderer()));
}

bool Game::isRunning() const
{
	return isRunning_;
}

void Game::shutDown()
{
	std::cout << "Freeing Resources" << std::endl;
	std::cout << "//////////////////" << std::endl;

	window_.release();
	resourceManager_.release();
	logicSystem_.release();
	physicsSystem_.release();
	renderSystem_.release();

	IMG_Quit();
	SDL_Quit();

	std::cout << "Game shutting down" << std::endl;
	std::cout << "//////////////////" << std::endl;
}

Window& Game::getWindow() const
{
	SDL_assert(window_ != nullptr);
	return *window_;
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

bool Game::initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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

bool Game::initWindow(const std::string& title, unsigned int width, unsigned int height, bool fullscreen)
{
	window_ = std::unique_ptr<Window>(new Window(title, width, height, fullscreen));

	if (!window_->init()) 
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

bool Game::initSystems()
{
	Input::initialize();

	resourceManager_ = std::unique_ptr<ResourceManager>(new ResourceManager(&(window_->getSdlRenderer())));
	logicSystem_ = std::unique_ptr<Logic>(new Logic(luaState_));
	physicsSystem_ = std::unique_ptr<Physics>(new Physics());
	renderSystem_ = std::unique_ptr<Renderer>(new Renderer(window_->getSdlRenderer(), *resourceManager_));

	return true;
}
