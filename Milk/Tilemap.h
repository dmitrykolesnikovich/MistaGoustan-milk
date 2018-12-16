#pragma once

#include <string>
#include <unordered_map>
#include <vector>

struct TilemapLayer;
struct TilemapTile;

class Texture;

struct Tilemap
{
	std::string source;
	int width;
	int height;
	int tilesize;
	Texture* texture;
	std::unordered_map<int, TilemapTile*> tileTypes;
	std::vector<TilemapLayer*> layers;
};
