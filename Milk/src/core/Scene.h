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

	// Spawns a new actor.
	Actor* spawnActor(const std::string& name);

	// Attempts to destroy and actor with the given id.
	// Returns true if successful.
	bool destroyActor(int id);

	// Attempts to find an actor with the given name.
	// Returns nullptr if not actor is found.
	Actor* findActor(const std::string& name);

	// Updates the scenes internal lists and notifies game when actors have been spawned, destroyed, or modified.
	void update();

private:
	Game& game_;

	std::unordered_map<int, std::unique_ptr<Actor>> actorsById_;
	std::vector<std::unique_ptr<Actor>> actorsToSpawn_;
	std::vector<int> actorsToDestroy_;

	IdGenerator idGenerator_;
};
