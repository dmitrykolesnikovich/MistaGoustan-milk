#include <memory>

#include "Scene.h"

#include "core/Actor.h"
#include "core/ActorComponent.h"
#include "utilities/Window.h"
#include "systems/EventQueue.h"
#include "systems/GameEvents.h"

Scene::Scene(Window& window, EventQueue& eventQueue)
	: eventQueue_(eventQueue)
	, camera_(*this, window.virtualWidth(), window.virtualHeight())
{
}

Scene::~Scene() = default;

Actor* Scene::spawnActor(const std::string& name)
{
	int id = idGenerator_.popId();

	auto actor = std::make_unique<Actor>(*this, id, name, Vector2d(0, 0));
	auto pActor = actor.get();

	actorsToSpawn_.emplace_back(std::move(actor));

	eventQueue_.pushEvent<ActorSpawnedEvent>(*pActor);

	return pActor;
}

bool Scene::destroyActor(int id)
{
	auto foundActor = actorsById_.find(id);

	if (foundActor == actorsById_.end())
		return false;

	actorsToDestroy_.emplace_back(id);

	eventQueue_.pushEvent<ActorDestroyedEvent>(*foundActor->second);

	return true;
}

Actor* Scene::findActor(const std::string& name) const
{
	// TODO: Brute force implementation. revisit.
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

void Scene::syncActorLists()
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

SDL_Rect Scene::bounds() const
{
	SDL_Rect bounds;
	bounds.x = 0;
	bounds.y = 0;
	bounds.w = tilemap_.width;
	bounds.h = tilemap_.height;

	return bounds;
}

void Scene::end()
{
	for (auto& it : actorsById_)
		destroyActor(it.first);

	for (auto& toSpawnItr : actorsToSpawn_)
		destroyActor(toSpawnItr->id());
}
