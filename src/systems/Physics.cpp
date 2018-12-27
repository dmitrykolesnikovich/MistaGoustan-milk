#include "Physics.h"

#include "../components/Velocity.h"
#include "../core/Actor.h"

void Physics::onActorAdded(Actor& actor)
{
	Velocity* velocity = actor.getComponent<Velocity>();

	if (velocity == nullptr)
		return;

	velocityByActorId_.insert(std::make_pair(actor.getId(), velocity));
}

void Physics::onActorDestroyed(Actor& actor)
{
	if (velocityByActorId_.find(actor.getId()) == velocityByActorId_.end())
		return;

	velocityByActorId_.erase(actor.getId());
}

void Physics::update()
{
	for (auto& it : velocityByActorId_)
	{
		Velocity* velocityComponent = it.second;
		Vector2d velocity = velocityComponent->getVelocity();

		Actor& actor = it.second->getActor();
		Vector2d actorPosition = actor.getPosition();
		Vector2d newPosition = actorPosition += velocity;

		actor.setPosition(newPosition);
	}
}
