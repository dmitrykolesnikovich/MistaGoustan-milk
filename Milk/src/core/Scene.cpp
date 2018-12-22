#include "Scene.h"

#include "Game.h"

Scene::Scene(Game& game)
	: _game(game)
{
}

Scene::~Scene()
{
}

Actor* Scene::spawnActor(const std::string& name)
{
	int id = _idGenerator.popId();

	auto actor = std::unique_ptr<Actor>(new Actor(*this));
	actor->_id = id;
	actor->_name = name;

	auto ptr = actor.get();

	_actorsToSpawn.emplace_back(std::move(actor));

	return ptr;
}

bool Scene::destroyActor(int id)
{
	if (_actorsById.find(id) == _actorsById.end())
		return false;

	_actorsToDestroy.emplace_back(id);

	return true;
}

Actor* Scene::findActor(const std::string& name)
{
	for (auto& it : _actorsById) 
	{
		if (it.second->getName() == name)
			return it.second.get();
	}

	return nullptr;
}

void Scene::update()
{
	for (auto& it : _actorsToDestroy) 
	{
		_actorsById.erase(it);
	}

	_actorsToDestroy.clear();

	auto& resourceManager = _game.getResourceManager();

	for (auto& it : _actorsToSpawn)
	{
		it->load(resourceManager);
		_actorsById.insert(std::make_pair(it->getId(), std::move(it)));
	}

	_actorsToSpawn.clear();
}

const std::unordered_map<int, std::unique_ptr<Actor>>& Scene::getAllActors()
{
	return _actorsById;
}
