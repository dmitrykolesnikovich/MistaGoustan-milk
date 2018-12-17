#pragma once

#include <vector>

#include "TilemapTileInstance.h"

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
