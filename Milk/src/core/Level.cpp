#include "Level.h"

#include <SDL.h>

#include "Game.h"
#include "GameObject.h"

#include "../utilities/ResourceManager.h"
#include "../utilities/Texture.h"
#include "../tilemap/Tilemap.h"

Level::Level(Game& game)
	: _game(game)
{
}

Level::~Level()
{
}

void Level::load()
{
	updateInternals();

	ResourceManager& resourceManager = _game.getResourceManager();

	for (auto it = _gameObjectsById.begin(); it != _gameObjectsById.end(); ++it) 	
		it->second->load(resourceManager);

	_tilemap.texture = resourceManager.loadTexture(_tilemap.sourceImageFile);
}

void Level::handleEvent(SDL_Event& e)
{
	for (auto it = _gameObjectsById.begin(); it != _gameObjectsById.end(); ++it)
		it->second->handleEvent(e);
}

void Level::update()
{
	updateInternals();

	for (auto it = _gameObjectsById.begin(); it != _gameObjectsById.end(); ++it)
		it->second->update();
}

void Level::render()
{
	SDL_Renderer& renderer = _game.getRenderer();
	SDL_Texture* tilemapTexture = _tilemap.texture->get();

	for (auto& layer : _tilemap.layers) 
	{
		for (auto& tile : layer->tiles) 
		{
			SDL_Rect dst;
			dst.x = tile->x;
			dst.y = tile->y;
			dst.w = tile->type.rect.w;
			dst.h = tile->type.rect.h;

			SDL_RenderCopyEx(&renderer, tilemapTexture, &tile->type.rect, &dst, 0, nullptr, SDL_FLIP_NONE);
		}
	}

	SDL_Rect destinationRect;

	for (auto it = _gameObjectsById.begin(); it != _gameObjectsById.end(); ++it)
	{
		GameObject* gameObject = it->second;
		Texture* texture = gameObject->getTexture();

		destinationRect.x = gameObject->position.x;
		destinationRect.y = gameObject->position.y;
		destinationRect.w = texture->getWidth();
		destinationRect.h = texture->getHeight();

		SDL_RenderCopy(&renderer, texture->get(), nullptr, &destinationRect);
	}
}

void Level::unload()
{
	for (auto it = _gameObjectsById.begin(); it != _gameObjectsById.end(); ++it)
	{
		delete it->second;
		it->second = nullptr;
	}

	for (auto it = _gameObjectsToAdd.begin(); it != _gameObjectsToAdd.end(); ++it)
	{
		delete *it;
		*it = nullptr;
	}

	for (auto it = _gameObjectsToDestroy.begin(); it != _gameObjectsToDestroy.end(); ++it)
	{
		delete *it;
		*it = nullptr;
	}
}

void Level::updateInternals()
{
	for (auto it = _gameObjectsToDestroy.begin(); it != _gameObjectsToDestroy.end(); ++it)
	{
		(*it)->end();
		unsigned int id = (*it)->getId();
		_gameObjectsById.erase(id);
	}

	_gameObjectsToDestroy.clear();

	for (auto it = _gameObjectsToAdd.begin(); it != _gameObjectsToAdd.end(); ++it)
	{
		(*it)->begin();
		std::pair<unsigned int, GameObject*> newInsert((*it)->getId(), (*it));
		_gameObjectsById.insert(newInsert);
	}

	_gameObjectsToAdd.clear();
}

GameObject& Level::createGameObject(const std::string& templateName) 
{
	GameObject* gameObject = _game.createFromFactory(templateName);
	gameObject->_id = _idGenerator.popId();

	_gameObjectsToAdd.emplace_back(gameObject);

	return *gameObject;
}
