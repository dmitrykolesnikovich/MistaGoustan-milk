#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Actor.h"

#include "../utilities/IdGenerator.h"

class Game;

class Scene 
{
public:
	Scene(Game& game);
	~Scene();

	Actor* spawnActor(const std::string& name);

	bool destroyActor(int id);

	Actor* findActor(const std::string& name);

	void update();

	const std::unordered_map<int, std::unique_ptr<Actor>>& getAllActors();

private:
	Game& _game;

	std::unordered_map<int, std::unique_ptr<Actor>> actorsById_;
	std::vector<std::unique_ptr<Actor>> actorsToSpawn_;
	std::vector<int> actorsToDestroy_;

	IdGenerator idGenerator_;
};
