#include "Game.h"

#include <iostream>

#include <SDL.h>
#include <SDL_events.h>

#include "GameObject.h"
#include "Level.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "LevelLoader.h"

Game::~Game()
{
}

Game& Game::getInstance() 
{
	static Game instance;
	return instance;
}

bool Game::init(const char* title, unsigned int width, unsigned int height, int flags)
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

	_window = SDL_CreateWindow(title, windowXPosition, windowYPosition, width, height, flags);

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

	_resourceManager = new ResourceManager();
	_resourceManager->init(_renderer);
	
	std::cout << "Game started" << std::endl;

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

		if (_currentLevel != nullptr)
			_currentLevel->handleEvent(e);
	}
}

void Game::update()
{
	if (_nextLevel != nullptr) 
	{
		if (_currentLevel != nullptr) 
		{
			_currentLevel->unload();

			delete _currentLevel;
			_currentLevel = nullptr;
		}
			
		_currentLevel = _nextLevel;

		_nextLevel = nullptr;

		_currentLevel->init();
		_currentLevel->load(*_resourceManager);
	}

	if (_currentLevel != nullptr)
		_currentLevel->update();
}

void Game::render()
{
	SDL_RenderClear(_renderer);

	if (_currentLevel != nullptr)
		_currentLevel->render();

	SDL_RenderPresent(_renderer);
}

bool Game::isRunning() const
{
	return _isRunning;
}

SDL_Renderer& Game::getRenderer()
{
	return *_renderer;
}

Level* Game::loadLevel(const char* filename)
{
	LevelLoader levelLoader;

	_nextLevel = levelLoader.load(*this, filename);

	return _nextLevel;
}

void Game::shutDown()
{
	std::cout << "Game shutting down" << std::endl;

	SDL_DestroyRenderer(_renderer);
	_renderer = nullptr;

	SDL_DestroyWindow(_window);
	_window = nullptr;

	SDL_Quit();
}

void Game::registerObjectFactory(const std::string& name, std::function<GameObject*(void)> factoryMethod)
{
	_gameObjectFactories[name] = factoryMethod;
}

GameObject* Game::createFromFactory(const std::string& name)
{
	return _gameObjectFactories[name]();
}
