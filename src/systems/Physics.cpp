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
		Actor& actor = it.second->actor();

		actor.position(actor.position() + velocity);

		BoxCollider* collider = it.second->actor().getComponent<BoxCollider>();
		collider->updateBBox();

		std::vector<Collision> collisions = collisionWorld_->getCollisions(collider);

		std::cout << collisions.size() << std::endl;
	}
}
