#include "ActorComponent.h"

ActorComponent::ActorComponent(Actor& actor)
	: actor_(actor)
{
}

ActorComponent::~ActorComponent()
{
}

Actor& ActorComponent::getActor()
{
	return actor_;
}
