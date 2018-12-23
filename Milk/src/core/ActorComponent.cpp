#include "ActorComponent.h"

ActorComponent::ActorComponent(Actor& actor)
	: actor_(actor)
{
}

ActorComponent::~ActorComponent()
{
}

Actor& ActorComponent::getActor() const
{
	return actor_;
}
