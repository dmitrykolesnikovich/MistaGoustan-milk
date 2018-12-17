#ifndef _LEVEL_LOADER_
#define _LEVEL_LOADER_

#include <memory>

class Level;

class LevelLoader
{
public:
	Level* build(const char* file);
};

#endif
