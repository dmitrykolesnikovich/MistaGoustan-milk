#ifndef _TILEMAP_
#define _TILEMAP_

#include <string>
#include <unordered_map>
#include <vector>

#include <SDL.h>

class Texture;

struct TileType
{
	TileType(int x, int y, int size)
	{
		rect.x = x;
		rect.y = y;
		rect.w = size;
		rect.h = size;
	}

	SDL_Rect rect;
};

struct TileInstance
{
	TileInstance(TileType& tile, int x, int y)
		: type(tile), x(x), y(y)
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
};

struct Tilemap
{
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
};

#endif // !_TILEMAP_
