#ifndef _SCENE_LOADER_
#define _SCENE_LOADER_

#include <memory>

#include "../core/Scene.h"

class Game;

class SceneLoader
{
public:
	SceneLoader(Game& game);
	~SceneLoader() = default;

	std::unique_ptr<Scene> load(const std::string& file) const;

private:
	Game& game_;
};

#endif
