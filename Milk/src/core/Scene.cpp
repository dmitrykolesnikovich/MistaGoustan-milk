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
	int id = idGenerator_.popId();

	auto actor = std::unique_ptr<Actor>(new Actor(*this));
	actor->_id = id;
	actor->_name = name;

	auto ptr = actor.get();

	actorsToSpawn_.emplace_back(std::move(actor));

	return ptr;
}

bool Scene::destroyActor(int id)
{
	if (actorsById_.find(id) == actorsById_.end())
		return false;

	actorsToDestroy_.emplace_back(id);

	return true;
}

Actor* Scene::findActor(const std::string& name)
{
	for (auto& it : actorsById_) 
	{
		if (it.second->getName() == name)
			return it.second.get();
	}

	return nullptr;
}

void Scene::update()
{
	for (auto& it : actorsToDestroy_) 
	{
		actorsById_.erase(it);
	}

	actorsToDestroy_.clear();

	auto& resourceManager = _game.getResourceManager();

	for (auto& it : actorsToSpawn_)
	{
		Actor* rawPtr = it.get();
		actorsById_.insert(std::make_pair(it->getId(), std::move(it)));

		_game.onActorAdded(*rawPtr);
	}

	actorsToSpawn_.clear();
}

const std::unordered_map<int, std::unique_ptr<Actor>>& Scene::getAllActors()
{
	return actorsById_;
}
