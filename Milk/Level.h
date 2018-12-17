#ifndef _LEVEL_
#define _LEVEL_

#include <string>
#include <unordered_map>
#include <vector>

union SDL_Event;

class Game;
class GameObject;
class ResourceManager;

struct Tilemap;

class Level
{
public:
	friend class LevelLoader;

	~Level();

	void init();
	void load();
	void handleEvent(SDL_Event& e);
	void update();
	void render();
	void unload();

private:
	Level(Game& game);

	Game& _game;

	std::unordered_map<unsigned int, GameObject*> _gameObjectsById;
	std::vector<GameObject*> _gameObjectsToAdd;
	std::vector<GameObject*> _gameObjectsToDestroy;

	Tilemap* _tilemap;

	void updateInternals();

};

#endif
