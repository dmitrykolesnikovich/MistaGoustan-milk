#include "DebugRenderer.h"

#include "../core/Actor.h"
#include "../core/Scene.h"

#include "../components/BoxCollider.h"

#include "../systems/ActorEventList.h"
#include "../systems/SpatialPartitionGrid.h"

DebugRenderer::DebugRenderer(SDL_Renderer& renderer)
	: sdlRenderer_(renderer)
{
}

void DebugRenderer::handleEvent(ActorEvent& gameEvent)
{
	switch (gameEvent.type())
	{
	case ActorEventType::ACTOR_SPAWNED: 
	{
		auto& spawnedEvent = dynamic_cast<ActorSpawnedEvent&>(gameEvent);
		onActorSpawned(spawnedEvent.actor());
	}		
		break;
	case ActorEventType::ACTOR_DETROYED: 
	{
		auto& destroyedEvent = dynamic_cast<ActorDestroyedEvent&>(gameEvent);
		onActorDestroyed(destroyedEvent.actor());
	}
		break;
	}
}

void DebugRenderer::onActorSpawned(Actor& actor)
{
	actorsById_.insert(std::make_pair(actor.id(), &actor));
}

void DebugRenderer::onActorDestroyed(Actor& actor)
{
	actorsById_.erase(actor.id());
}

void DebugRenderer::render(Scene& scene)
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
