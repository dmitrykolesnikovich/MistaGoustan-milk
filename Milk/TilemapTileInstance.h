#pragma once

struct TilemapTile;

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