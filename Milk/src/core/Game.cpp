#include "Game.h"

#include <iostream>

#include <SDL.h>
#include <SDL_events.h>

#include "../utilities/ResourceManager.h"
#include "../utilities/Texture.h"
#include "Scene.h"
#include "../components/Sprite.h"
#include "../components/Velocity.h"

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
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
	{
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
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

	isRunning_ = true;

	resourceManager_ = std::unique_ptr<ResourceManager>(new ResourceManager(sdlRenderer_));

	// test
	currentScene_ = std::unique_ptr<Scene>(new Scene(*this));
	auto actor = currentScene_->spawnActor("steve");
	actor->addComponent<Sprite>();
	auto sprite = actor->getComponent<Sprite>();
	sprite->setTextureName("res/steve.png");
	sprite->setSourceRect(0, 0, 64, 64);
	actor->addComponent<Velocity>();
	auto velocity = actor->getComponent<Velocity>();
	velocity->setVelocity(1, 0);

	physicsSystem_ = std::unique_ptr<Physics>(new Physics());
	renderSystem_ = std::unique_ptr<Renderer>(new Renderer(*sdlRenderer_, *resourceManager_));
	
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
			case SDL_KEYDOWN:
				if (e.key.keysym.sym == SDLK_SPACE)
					currentScene_->destroyActor(currentScene_->findActor("steve")->getId());
				break;
			default:
				break;
		}
	}
}

void Game::update()
{
	currentScene_->update();
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
	physicsSystem_->onActorAdded(actor);
	renderSystem_->onActorAdded(actor);
}

void Game::onActorDestroyed(Actor& actor)
{
	physicsSystem_->onActorDestroyed(actor);
	renderSystem_->onActorDestroyed(actor);
}
