#ifndef _LEVEL_LOADER_
#define _LEVEL_LOADER_

class Game;
class Level;

class LevelLoader
{
public:
	Level* load(Game& game, const char* file);
};

#endif
