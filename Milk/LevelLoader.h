#ifndef _LEVEL_LOADER_
#define _LEVEL_LOADER_

#include <string>

class Game;
class Level;

class LevelLoader
{
public:
	Level* load(Game& game, const std::string& file);
};

#endif
