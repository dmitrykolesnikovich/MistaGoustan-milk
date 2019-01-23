#ifndef _SCENE_LOADER_
#define _SCENE_LOADER_

#include <memory>

class Game;
class Scene;

class SceneLoader
{
public:
	explicit SceneLoader(Game& game);
	~SceneLoader();

	std::unique_ptr<Scene> load(const std::string& file) const;

private:
	Game& game_;
};

#endif
