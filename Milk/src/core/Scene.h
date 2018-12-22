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

private:
	Game& _game;

	std::unordered_map<int, std::unique_ptr<Actor>> _actorsById;
	std::vector<std::unique_ptr<Actor>> _actorsToAdd;
	std::vector<int> _actorsToRemove;

	IdGenerator _idGenerator;
};
