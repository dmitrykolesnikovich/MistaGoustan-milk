#include "Physics.h"

#include <vector>

#include "../components/BoxCollider.h"
#include "../components/Velocity.h"

#include "../core/Actor.h"

Physics::Physics()
	: partitionGrid_(new SpatialPartitionGrid())
{
}

void Physics::onActorAdded(Actor& actor)
{
	Velocity* velocity = actor.getComponent<Velocity>();	

	if (velocity != nullptr)
		velocityByActorId_.insert(std::make_pair(actor.id(), velocity));

	BoxCollider* collider = actor.getComponent<BoxCollider>();

	if (collider != nullptr) 
	{
		collider->init(partitionGrid_.get());
		partitionGrid_->add(collider);
	}
}

void Physics::onActorDestroyed(Actor& actor)
{
	if (velocityByActorId_.find(actor.id()) != velocityByActorId_.end())
		velocityByActorId_.erase(actor.id());

	BoxCollider* collider = actor.getComponent<BoxCollider>();
	
	if (collider != nullptr)
		partitionGrid_->remove(collider);
}

void Physics::update()
{
	for (auto& it : velocityByActorId_) 
	{
		Vector2d velocity = it.second->value();

		if (velocity == Vector2d(0, 0))
			continue;

		Actor& actor = it.second->actor();
		Vector2d oldActorPosition = actor.position();

		actor.position(actor.position() + velocity);

		BoxCollider* collider = it.second->actor().getComponent<BoxCollider>();
		collider->updateBBox();

		// Get collision events from collision world.
		std::vector<CollisionEvent> collisions = partitionGrid_->getCollisions(collider);

		// Resolve the collisions: 
		// Collision events contain a collision side and intersection depth rectangle.
		// In the future, these two values can be used to create a more accurate collision.
		// For now, simply reverting back to the actors previous axis position is fine.
		for (auto it : collisions) 
		{
			auto pos = actor.position();

			actor.position(actor.position().x, oldActorPosition.y);
			collider->updateBBox();

			if (collider->overlaps(it.other->rect())) 
			{
				actor.position(oldActorPosition.x, pos.y);
				collider->updateBBox();
			}
		}
	}
}
