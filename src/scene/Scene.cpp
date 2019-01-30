#include <memory>

#include "Scene.h"

#include "scene/Actor.h"
#include "scene/ActorComponent.h"
#include "events/EventQueue.h"
#include "events/GameEvents.h"
#include "window/Window.h"

milk::Scene::Scene(milk::EventQueue& eventQueue, unsigned virtualWidth, unsigned virtualHeight)
        : eventQueue_(eventQueue),
          camera_(*this, virtualWidth, virtualHeight),
          ended_(false)
{
}

milk::Scene::~Scene() = default;

milk::Actor* milk::Scene::spawnActor(const std::string& name)
{
    int id = idGenerator_.popId();

    auto actor = std::make_unique<Actor>(id, name, Vector2d(0, 0));
    auto pActor = actor.get();

    actorsToSpawn_.emplace_back(std::move(actor));

    // If the scene has been unloaded, then let's not push an actor spawned event.
    // We don't want any systems to hold a reference to an invalid actor.
    if (!ended_)
        eventQueue_.pushEvent<ActorSpawnedEvent>(*pActor);

    return pActor;
}

bool milk::Scene::destroyActor(int id)
{
    auto foundActor = actorsById_.find(id);

    if (foundActor == actorsById_.end())
        return false;

    actorsToDestroy_.emplace_back(id);

    // We can push actor destroyed events whenever. If a system is written properly,
    // it will check if it even holds a reference to the actor before making any decisions.
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

milk::Rectangle milk::Scene::bounds() const
{
    return { 0, 0, tilemap_.width, tilemap_.height };
}

void milk::Scene::end()
{
    ended_ = true;
}
