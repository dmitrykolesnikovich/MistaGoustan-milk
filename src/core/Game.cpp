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

bool Game::init(const std::string& title, unsigned int width, unsigned int height, int flags)
{
	if (!initSDL(title, width, height, flags)) 
	{
		std::cout << "Shutting down early." << std::endl;
		return false;
	}

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
	SDL_RenderClear(sdlRenderer_);

	renderSystem_->render();

	SDL_RenderPresent(sdlRenderer_);
}

bool Game::isRunning() const
{
	return isRunning_;
}

SDL_Renderer& Game::getRenderer() const
{
	SDL_assert(sdlRenderer_ != nullptr);
	return *sdlRenderer_;
}

ResourceManager& Game::getResourceManager() const 
{
	SDL_assert(resourceManager_);
	return *(resourceManager_.get());
}

void Game::shutDown()
{
	std::cout << "Freeing Resources" << std::endl;
	std::cout << "//////////////////" << std::endl;
	
	SDL_DestroyRenderer(sdlRenderer_);
	sdlRenderer_ = nullptr;

	SDL_DestroyWindow(window_);
	window_ = nullptr;

	SDL_Quit();

	std::cout << "Game shutting down" << std::endl;
	std::cout << "//////////////////" << std::endl;
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

bool Game::initSDL(const std::string& title, unsigned int width, unsigned int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return false;
	}

	int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(imgFlags);
	if ((initted & imgFlags) != imgFlags)
	{
		std::cout << "Error initializing SDL_image: " << IMG_GetError() << std::endl;
		return false;
	}

	SDL_DisplayMode currentDisplayMode;
	SDL_GetCurrentDisplayMode(0, &currentDisplayMode);

	int windowXPosition = (currentDisplayMode.w / 2) - (width / 2);
	int windowYPosition = (currentDisplayMode.h / 2) - (height / 2);

	window_ = SDL_CreateWindow(title.c_str(), windowXPosition, windowYPosition, width, height, flags);

	if (window_ == nullptr)
	{
		std::cout << "Error creating window: " << SDL_GetError() << std::endl;
		return false;
	}

	sdlRenderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (sdlRenderer_ == nullptr)
	{
		std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
	SDL_RenderSetLogicalSize(sdlRenderer_, width, height);
	SDL_SetRenderDrawColor(sdlRenderer_, 0x00, 0x00, 0x00, 0xff);

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

	resourceManager_ = std::unique_ptr<ResourceManager>(new ResourceManager(sdlRenderer_));
	logicSystem_ = std::unique_ptr<Logic>(new Logic(luaState_));
	physicsSystem_ = std::unique_ptr<Physics>(new Physics());
	renderSystem_ = std::unique_ptr<Renderer>(new Renderer(*sdlRenderer_, *resourceManager_));

	return true;
}
