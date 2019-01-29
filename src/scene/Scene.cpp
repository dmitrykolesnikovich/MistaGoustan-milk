#include <memory>

#include "Scene.h"

#include "scene/Actor.h"
#include "scene/ActorComponent.h"
#include "events/EventQueue.h"
#include "events/GameEvents.h"
#include "window/Window.h"

milk::Scene::Scene(milk::EventQueue& eventQueue, unsigned virtualWidth, unsigned virtualHeight)
        : eventQueue_(eventQueue),
          camera_(*this, virtualWidth, virtualHeight)
{
}

milk::Scene::~Scene() = default;

milk::Actor* milk::Scene::spawnActor(const std::string& name)
{
    int id = idGenerator_.popId();

    auto actor = std::make_unique<Actor>(id, name, Vector2d(0, 0));
    auto pActor = actor.get();

    actorsToSpawn_.emplace_back(std::move(actor));

    eventQueue_.pushEvent<ActorSpawnedEvent>(*pActor);

    return pActor;
}

bool milk::Scene::destroyActor(int id)
{
    auto foundActor = actorsById_.find(id);

    if (foundActor == actorsById_.end())
        return false;

    actorsToDestroy_.emplace_back(id);

    eventQueue_.pushEvent<ActorDestroyedEvent>(*foundActor->second);

    return true;
}

milk::Actor* milk::Scene::findActor(const std::string& name) const
{
    // TODO: Brute force implementation. revisit.
    for (auto& it : actorsById_)
    {
        if (it.second->name() == name)
            return it.second.get();
    }

    return nullptr;
}

milk::Camera& milk::Scene::camera()
{
    return camera_;
}

milk::Tilemap& milk::Scene::tilemap()
{
    return tilemap_;
}

void milk::Scene::syncActorLists()
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

SDL_Rect milk::Scene::bounds() const
{
    SDL_Rect bounds;
    bounds.x = 0;
    bounds.y = 0;
    bounds.w = tilemap_.width;
    bounds.h = tilemap_.height;

    return bounds;
}

void milk::Scene::end()
{
    for (auto& it : actorsById_)
        destroyActor(it.first);

    for (auto& toSpawnItr : actorsToSpawn_)
        destroyActor(toSpawnItr->id());
}
