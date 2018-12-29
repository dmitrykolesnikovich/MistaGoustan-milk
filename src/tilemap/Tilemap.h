#ifndef _TILEMAP_
#define _TILEMAP_

#include <string>
#include <unordered_map>
#include <vector>

#include "SDL.h"

class Texture;

struct TileType
{
	TileType(int x, int y, int size, bool coll)
	{
		sourceRect.x = x;
		sourceRect.y = y;
		sourceRect.w = size;
		sourceRect.h = size;
		collidable = coll;
	}

	SDL_Rect sourceRect;
	bool collidable;

	// Additional information about the type will go here.
	// i.e. triggerable, opacity, animations.
};

struct TileInstance
{
	TileInstance(TileType& tile, int x, int y)
		: type(tile)
		, x(x)
		, y(y)
	{
	}

	int x;
	int y;

	TileType& type;
};


struct TileLayer
{
	~TileLayer() 
	{
		for (auto& it : tiles) 
		{
			delete it;
			it = nullptr;
		}
	}

	std::vector<TileInstance*> tiles;

	void addTile(TileType& type, int x, int y) 
	{
		tiles.emplace_back(new TileInstance(type, x, y));
	}
};

struct Tilemap
{
	Tilemap() 
		: sourceImageFile("")
		, width(0)
		, height(0)
		, tileSize(0)
		, texture(nullptr)
	{
	}

	~Tilemap() 
	{
		for (auto& it : tileTypes) 
		{
			delete it.second;
			it.second = nullptr;
		}

		for (auto& it : layers) 
		{
			delete it;
			it = nullptr;
		}
	}

	std::string sourceImageFile;
	int width;
	int height;
	int tileSize;

	Texture* texture;

	std::unordered_map<int, TileType*> tileTypes;
	std::vector<TileLayer*> layers;

	TileType& addTileType(int id, int x, int y, bool collidable) 
	{
		TileType* type = new TileType(x, y, tileSize, collidable);
		tileTypes.insert(std::pair<int, TileType*>(id, type));

		return *type;
	}

	TileLayer& addLayer() 
	{
		TileLayer* layer = new TileLayer();
		layers.emplace_back(layer);

		return *layer;
	}
};

#endif
