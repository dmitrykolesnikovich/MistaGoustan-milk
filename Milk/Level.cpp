#include "Level.h"

#include <SDL.h>

#include "Game.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Tilemap.h"
#include "TilemapLayer.h"
#include "TilemapTile.h"
#include "TilemapTileInstance.h"

Level::Level(Game& game)
	: _game(game)
{
}

Level::~Level()
{
}

void Level::init()
{
	updateInternals();
}

void Level::load(ResourceManager& resourceManager)
{
	for (auto it = _gameObjectsById.begin(); it != _gameObjectsById.end(); ++it) 	
		it->second->load(resourceManager);

	_tilemap->texture = resourceManager.loadTexture(_tilemap->source);
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

	for (auto& layer : _tilemap->layers) 
	{
		for (auto& tile : layer->tiles) 
		{
			SDL_Rect dst;
			dst.x = tile->x;
			dst.y = tile->y;
			dst.w = tile->tile.rect.w;
			dst.h = tile->tile.rect.h;

			SDL_RenderCopyEx(&renderer, _tilemap->texture->get(), &tile->tile.rect, &dst, 0, nullptr, SDL_FLIP_NONE);
		}
	}

	SDL_Rect destinationRect;

	for (auto it = _gameObjectsById.begin(); it != _gameObjectsById.end(); ++it)
	{
		GameObject* gameObject = it->second;
		Texture* texture = gameObject->getTexture();

		destinationRect.x = gameObject->getX();
		destinationRect.y = gameObject->getY();
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

	delete _tilemap;
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
