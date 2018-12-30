#include "Physics.h"

#include <vector>

#include "../components/BoxCollider.h"
#include "../components/Velocity.h"

#include "../core/Actor.h"

#include <iostream>

Physics::Physics()
	: collisionWorld_(new SpatialPartitionGrid())
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
		collider->init(collisionWorld_.get());
		collisionWorld_->add(collider);
	}
}

void Physics::onActorDestroyed(Actor& actor)
{
}

void Physics::update()
{
	for (auto& it : velocityByActorId_) 
	{
		Vector2d velocity = it.second->value();

		if (velocity == Vector2d(0, 0))
			continue;

		Actor& actor = it.second->actor();

		Vector2d actorOldPos = actor.position();

		actor.position(actor.position() + velocity);

		BoxCollider* collider = it.second->actor().getComponent<BoxCollider>();
		collider->updateBBox();

		std::vector<Collision> collisions = collisionWorld_->getCollisions(collider);

		// Resolve collisions 
		// TODO notify scripts of collision event
		for (auto it : collisions) 
		{
			switch (it.direction) 
			{
			case (CollisionDirection::TOP):
				actor.position(actor.position().x, actorOldPos.y);
				break;
			case (CollisionDirection::BOTTOM):
				actor.position(actor.position().x, actorOldPos.y);
				break;
			case (CollisionDirection::RIGHT):
				actor.position(actorOldPos.x, actor.position().y);
				break;
			case (CollisionDirection::LEFT):
				actor.position(actorOldPos.x, actor.position().y);
				break;
			}
		}

		collider->updateBBox();
	}
}
