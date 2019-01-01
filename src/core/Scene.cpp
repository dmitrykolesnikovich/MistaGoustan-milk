#include "Scene.h"

#include "Game.h"

#include "../systems/ActorEventList.h"

Scene::Scene(Game& game)
	: game_(game)
	, camera_(*this, game.window().virtualWidth(), game.window().virtualHeight())
{
}

Actor* Scene::spawnActor(const std::string& name)
{
	int id = idGenerator_.popId();

	auto actor = std::unique_ptr<Actor>(new Actor(*this, id, name, Vector2d(0, 0)));

	auto ptr = actor.get();

	actorsToSpawn_.emplace_back(std::move(actor));

	game_.eventQueue().pushEvent(new ActorSpawnedEvent(*ptr));

	return ptr;
}

bool Scene::destroyActor(int id)
{
	auto foundActor = actorsById_.find(id);

	if (foundActor == actorsById_.end())
		return false;

	game_.eventQueue().pushEvent(new ActorSpawnedEvent(*foundActor->second));

	actorsToDestroy_.emplace_back(id);

	return true;
}

Actor* Scene::findActor(const std::string& name) const
{
	for (auto& it : actorsById_) 
	{
		if (it.second->name() == name)
			return it.second.get();
	}

	return nullptr;
}

Camera& Scene::camera()
{
	return camera_;
}

Tilemap& Scene::tilemap()
{
	return tilemap_;
}

void Scene::update()
{
	for (auto& it : actorsToDestroy_) 
	{
		idGenerator_.pushId(it);
		actorsById_.erase(it);
	}

	actorsToDestroy_.clear();

	for (auto& it : actorsToSpawn_)	
		actorsById_.insert(std::make_pair(it->id(), std::move(it)));	

	actorsToSpawn_.clear();
}

void Scene::unload() const
{
	for (auto& it : actorsById_)
	{
		//game_.onActorDestroyed(*it.second);
	}
}

SDL_Rect Scene::bounds() const
{
	SDL_Rect bounds;
	bounds.x = 0;
	bounds.y = 0;
	bounds.w = tilemap_.width;
	bounds.h = tilemap_.height;

	return bounds;
}
