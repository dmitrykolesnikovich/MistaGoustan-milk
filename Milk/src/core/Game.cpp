#include "Game.h"

#include <iostream>

#include <SDL.h>
#include <SDL_events.h>

#include "../utilities/ResourceManager.h"
#include "../utilities/Texture.h"
#include "Scene.h"
#include "../components/Sprite.h"

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

	_window = SDL_CreateWindow(title.c_str(), windowXPosition, windowYPosition, width, height, flags);

	if (_window == nullptr) 
	{
		std::cout << "Error creating window: " << SDL_GetError() << std::endl;
		return false;
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (_renderer == nullptr) 
	{
		std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
	SDL_RenderSetLogicalSize(_renderer, width, height);
	SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xff);

	_isRunning = true;

	_resourceManager = std::unique_ptr<ResourceManager>(new ResourceManager(_renderer));

	// test
	_currentScene = std::unique_ptr<Scene>(new Scene(*this));
	auto actor = _currentScene->spawnActor("steve");
	actor->addComponent<Sprite>();
	auto sprite = actor->getComponent<Sprite>();
	sprite->setTextureName("res/steve.png");
	sprite->setSourceRect(0, 0, 64, 64);

	_renderSystem = std::unique_ptr<Renderer>(new Renderer(*_renderer, *_resourceManager));
	
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
				_isRunning = false;
				break;
			case SDL_KEYUP:
				if (e.key.keysym.sym == SDLK_ESCAPE)
					_isRunning = false;
			default:
				break;
		}
	}
}

void Game::update()
{
	_currentScene->update();
}

void Game::render()
{
	SDL_RenderClear(_renderer);

	_renderSystem->update(*_currentScene);

	SDL_RenderPresent(_renderer);
}

bool Game::isRunning() const
{
	return _isRunning;
}

SDL_Renderer& Game::getRenderer() const
{
	SDL_assert(_renderer != nullptr);
	return *_renderer;
}

ResourceManager& Game::getResourceManager() const 
{
	SDL_assert(_resourceManager);
	return *(_resourceManager.get());
}

void Game::shutDown()
{
	std::cout << "Freeing Resources" << std::endl;
	std::cout << "//////////////////" << std::endl;
	
	SDL_DestroyRenderer(_renderer);
	_renderer = nullptr;

	SDL_DestroyWindow(_window);
	_window = nullptr;

	SDL_Quit();

	std::cout << "Game shutting down" << std::endl;
	std::cout << "//////////////////" << std::endl;
}

void Game::onActorAdded(Actor& actor)
{
	_renderSystem->onActorAdded(actor);
}
