#pragma once

#include <vector>

#include "TilemapTileInstance.h"

struct TilemapLayer
{
	std::vector<TilemapTileInstance*> tiles;
};
