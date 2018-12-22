#include "ActorComponent.h"

ActorComponent::ActorComponent(Actor& actor)
	: _actor(actor)
{
}

ActorComponent::~ActorComponent()
{
}

void ActorComponent::load(ResourceManager& resourceManager)
{
}
