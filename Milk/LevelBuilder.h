#ifndef _LEVEL_BUILDER_
#define _LEVEL_BUILDER_

#include <memory>

class Level;

class LevelBuilder
{
public:
	std::unique_ptr<Level> build(const char* file);
};

#endif
