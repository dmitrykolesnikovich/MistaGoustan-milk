#ifndef _LEVEL_LOADER_
#define _LEVEL_LOADER_

#include <string>

class Game;
class Level;

class LevelLoader
{
public:
	LevelLoader(Game& game);

	// Load level from XML level file.
	Level* load(const std::string& file);

private:
	Game& _game;
};

#endif
