#include "DebugTools.h"

#include "scene/Actor.h"
#include "scene/Scene.h"

#include "events/GameEvents.h"

#include "physics/BoxCollider.h"
#include "physics/SpatialPartitionGrid.h"

milk::DebugTools::DebugTools(SDL_Renderer& renderer)
        : sdlRenderer_(renderer)
{
}

void milk::DebugTools::handleEvent(GameEvent& gameEvent)
{
    switch (gameEvent.type())
    {
        case GameEventType::ACTOR_SPAWNED:
        {
            auto& spawnedEvent = dynamic_cast<ActorSpawnedEvent&>(gameEvent);
            onActorSpawned(spawnedEvent.actor());
        }
            break;
        case GameEventType::ACTOR_DETROYED:
        {
            auto& destroyedEvent = dynamic_cast<ActorDestroyedEvent&>(gameEvent);
            onActorDestroyed(destroyedEvent.actor());
        }
            break;
        default:
            break;
    }
}

void milk::DebugTools::onActorSpawned(Actor& actor)
{
    actorsById_.insert(std::make_pair(actor.id(), &actor));
}

void milk::DebugTools::onActorDestroyed(Actor& actor)
{
    actorsById_.erase(actor.id());
}

void milk::DebugTools::render(Scene& scene)
{
    if (!show)
        return;

    int cells = SpatialPartitionGrid::NUM_CELLS;
    int size = SpatialPartitionGrid::CELL_SIZE;

    for (int i = 0; i < cells; i++)
    {
        for (int j = 0; j < cells; j++)
        {
            SDL_Rect dest;
            dest.x = j * size - scene.camera().position().x;
            dest.y = i * size - scene.camera().position().y;
            dest.w = size;
            dest.h = size;

            SDL_SetRenderDrawColor(&sdlRenderer_, 0x00, 0xff, 0x00, 90);
            SDL_RenderDrawRect(&sdlRenderer_, &dest);
        }
    }

    for (auto it : actorsById_)
    {
        auto coll = it.second->getComponent<BoxCollider>();

        if (coll != nullptr)
        {
            SDL_Rect destinationRect = coll->rect();
            destinationRect.x -= scene.camera().position().x;
            destinationRect.y -= scene.camera().position().y;
            SDL_SetRenderDrawColor(&sdlRenderer_, 0xFF, 0x00, 0x00, 75);
            SDL_RenderFillRect(&sdlRenderer_, &destinationRect);
        }
    }
}
