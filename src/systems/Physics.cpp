#include "Physics.h"

#include <vector>

#include "components/BoxCollider.h"
#include "components/Velocity.h"

#include "core/Actor.h"

#include "systems/EventQueue.h"
#include "systems/GameEvents.h"
#include "systems/SpatialPartitionGrid.h"

Physics::Physics(EventQueue& eventQueue)
        : eventQueue_(eventQueue), partitionGrid_(new SpatialPartitionGrid()) {
}

Physics::~Physics() = default;

void Physics::handleEvent(GameEvent& gameEvent) {
    switch (gameEvent.type()) {
        case GameEventType::ACTOR_SPAWNED: {
            auto& spawnedEvent = dynamic_cast<ActorSpawnedEvent&>(gameEvent);
            onActorSpawned(spawnedEvent.actor());
        }
            break;
        case GameEventType::ACTOR_DETROYED: {
            auto& destroyedEvent = dynamic_cast<ActorDestroyedEvent&>(gameEvent);
            onActorDestroyed(destroyedEvent.actor());
        }
            break;
        default:
            break;
    }
}

void Physics::update() {
    for (auto& velItr : velocityByActorId_) {
        Vector2d velocity = velItr.second->value();

        if (velocity == Vector2d(0, 0))
            continue;

        Actor& actor = velItr.second->actor();
        Vector2d oldActorPosition = actor.position();

        auto newPos = actor.position() + velocity;
        actor.position(newPos.x, newPos.y);

        auto collider = velItr.second->actor().getComponent<BoxCollider>();

        if (collider == nullptr)
            continue;

        collider->updateBBox();

        // Get collision events from collision world.
        auto collisions = partitionGrid_->getCollisions(collider);

        // Resolve the collisions:
        // Collision events contain a collision side and intersection depth rectangle.
        // In the future, these two values can be used to create a more accurate collision.
        // For now, simply reverting back to the actors previous axis position is fine.
        for (auto collItr : collisions) {
            eventQueue_.pushEvent<ActorCollisionEvent>(actor, *collItr.other);

            auto pos = actor.position();

            actor.position(actor.position().x, oldActorPosition.y);
            collider->updateBBox();

            if (collider->overlaps(collItr.other->rect())) {
                actor.position(oldActorPosition.x, pos.y);
                collider->updateBBox();
            }
        }
    }
}

void Physics::onActorSpawned(Actor& actor) {
    auto velocity = actor.getComponent<Velocity>();

    if (velocity != nullptr)
        velocityByActorId_.insert(std::make_pair(actor.id(), velocity));

    auto collider = actor.getComponent<BoxCollider>();

    if (collider != nullptr) {
        collider->init(partitionGrid_.get());
        partitionGrid_->add(collider);
    }
}

void Physics::onActorDestroyed(Actor& actor) {
    if (velocityByActorId_.find(actor.id()) != velocityByActorId_.end())
        velocityByActorId_.erase(actor.id());

    auto collider = actor.getComponent<BoxCollider>();

    if (collider != nullptr)
        partitionGrid_->remove(collider);
}
