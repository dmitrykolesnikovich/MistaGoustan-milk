#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class Game;
class GameObject;
class ResourceManager;

struct Tilemap;

union SDL_Event;

class Level
{
public:
	friend class LevelLoader;

	Level();
	~Level();

	void init(Game* game);
	void load(ResourceManager& resourceManager);
	void handleEvent(SDL_Event& e);
	void update();
	void render();
	void unload();

	template<class T>
	GameObject* createGameObject(const std::string& name) 
	{
		GameObject* gameObject = new T(name);
		_gameObjectsToAdd.push_back(gameObject);
		return gameObject;
	}

	void destroyGameObject(GameObject* gameObject);

	GameObject* findGameObject(std::string& name) const;
	GameObject* findGameObject(unsigned int id) const;

private:
	Game* _game;

	std::unordered_map<unsigned int, GameObject*> _gameObjectsById;
	std::vector<GameObject*> _gameObjectsToAdd;
	std::vector<GameObject*> _gameObjectsToDestroy;

	Tilemap* _tilemap;

	void updateInternals();

};
