#ifndef _LEVEL_
#define _LEVEL_

#include <string>
#include <unordered_map>
#include <vector>

#include "IdGenerator.h"
#include "Tilemap.h"

union SDL_Event;

class Game;
class GameObject;
class ResourceManager;

class Level
{
public:
	friend class LevelLoader;

	~Level();

	// Load the levels resources.
	void load();

	// Pass events to level so it can handle them.
	void handleEvent(SDL_Event& e);

	// Update game objects, tile maps, etc...
	void update();

	// Render game objects, tile maps, etc...
	void render();

	// Free all of levels resources.
	void unload();

	// Creates a game object and returns it.
	GameObject& createGameObject(const std::string& templateName);

private:
	Level(Game& game);

	Game& _game;

	std::unordered_map<unsigned int, GameObject*> _gameObjectsById;
	std::vector<GameObject*> _gameObjectsToAdd;
	std::vector<GameObject*> _gameObjectsToDestroy;

	Tilemap _tilemap;

	IdGenerator _idGenerator;

	void updateInternals();
};

#endif
