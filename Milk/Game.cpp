#include "Game.h"

#include <iostream>

#include <SDL.h>
#include <SDL_events.h>

#include "GameObject.h"
#include "Level.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "LevelBuilder.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::init(const char* title, unsigned int width, unsigned int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
	{
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);

	int displayWidth = displayMode.w;
	int displayHeight = displayMode.h;

	int x = (displayWidth / 2) - (width / 2);
	int y = (displayHeight / 2) - (height / 2);

	_window = SDL_CreateWindow(title, x, y, width, height, flags);

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

	ResourceManager::init(_renderer);
	
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

		_currentLevel->init(this);
		_currentLevel->load();
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

void Game::loadLevel(Level* level)
{
	_nextLevel = level;
}

Level* Game::loadLevel(const char* filename)
{
	LevelBuilder lvlBuilder;
	_nextLevel = lvlBuilder.build(filename);
	return _nextLevel;
}

void Game::shutDown()
{
	std::cout << "Game shutting down" << std::endl;

	if (_currentLevel != nullptr) 
	{
		_currentLevel->unload();
		delete _currentLevel;
		_currentLevel = nullptr;
	}
	
	if (_nextLevel != nullptr) 
	{
		delete _nextLevel;
		_nextLevel = nullptr;
	}

	SDL_DestroyRenderer(_renderer);
	_renderer = nullptr;

	SDL_DestroyWindow(_window);
	_window = nullptr;

	SDL_Quit();
}
