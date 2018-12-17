#ifndef _TILEMAP_
#define _TILEMAP_

#include <string>
#include <unordered_map>
#include <vector>

#include <SDL.h>

class Texture;

struct TilemapTile
{
	TilemapTile(int x, int y, int size)
	{
		rect.x = x;
		rect.y = y;
		rect.w = size;
		rect.h = size;
	}

	SDL_Rect rect;
};

struct TilemapTileInstance
{
	TilemapTileInstance(TilemapTile& tile, int x, int y)
		: tile(tile), x(x), y(y)
	{
	}

	int x;
	int y;
	TilemapTile& tile;
};


struct TilemapLayer
{
	TilemapLayer()
	{
		for (auto& it : tiles)
		{
			delete it;
			it = nullptr;
		}
	}

	std::vector<TilemapTileInstance*> tiles;
};

struct Tilemap
{
	Tilemap()
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

	std::string source;
	int width;
	int height;
	int tilesize;
	Texture* texture;
	std::unordered_map<int, TilemapTile*> tileTypes;
	std::vector<TilemapLayer*> layers;
};

#endif // !_TILEMAP_
