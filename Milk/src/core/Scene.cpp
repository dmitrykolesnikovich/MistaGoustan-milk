#include "Scene.h"

#include "Game.h"

Scene::Scene(Game& game)
	: game_(game)
{
}

Scene::~Scene()
{
}

Actor* Scene::spawnActor(const std::string& name)
{
	int id = idGenerator_.popId();

	auto actor = std::unique_ptr<Actor>(new Actor(*this));
	actor->id_ = id;
	actor->name_ = name;

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
		auto& actor = *actorsById_.at(it);

		game_.onActorDestroyed(actor);

		idGenerator_.pushId(it);

		actorsById_.erase(it);
	}

	actorsToDestroy_.clear();

	for (auto& it : actorsToSpawn_)
	{
		Actor* rawPtr = it.get();
		actorsById_.insert(std::make_pair(it->getId(), std::move(it)));

		game_.onActorSpawned(*rawPtr);
	}

	actorsToSpawn_.clear();
}
