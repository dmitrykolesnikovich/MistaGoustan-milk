#include "PlayerBehavior.h"

#include "../core/Actor.h"
#include "../components/Velocity.h"

const ComponentType PlayerBehavior::type = BEHAVIOR;

PlayerBehavior::PlayerBehavior(Actor& actor)
	: Behavior::Behavior(actor)
{
}

void PlayerBehavior::begin()
{
	vel_ = actor_.getComponent<Velocity>();
	vel_->setVelocity(0, 1);
}
