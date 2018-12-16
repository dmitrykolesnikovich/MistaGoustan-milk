#pragma once

#include <SDL.h>

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

