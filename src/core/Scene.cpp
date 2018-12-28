#include "Scene.h"

#include "Game.h"

Scene::Scene(Game& game)
	: game_(game)
{
	tilemap_ = Tilemap();
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

Actor* Scene::findActor(const std::string& name) const
{
	for (auto& it : actorsById_) 
	{
		if (it.second->getName() == name)
			return it.second.get();
	}

	return nullptr;
}

Tilemap& Scene::getTilemap()
{
	return tilemap_;
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
		actorsById_.insert(std::make_pair(it->id(), std::move(it)));

		game_.onActorSpawned(*rawPtr);
	}

	actorsToSpawn_.clear();
}

void Scene::unload() const
{
	for (auto& it : actorsById_)
	{
		game_.onActorDestroyed(*it.second);
	}
}
