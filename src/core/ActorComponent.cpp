#include "ActorComponent.h"

ActorComponent::ActorComponent(Actor& actor)
	: actor_(actor)
{
}

ActorComponent::~ActorComponent()
{
}

Actor& ActorComponent::actor() const
{
	return actor_;
}
