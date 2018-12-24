#include "Behavior.h"

const ComponentType Behavior::type = BEHAVIOR;

Behavior::Behavior(Actor& actor)
	: ActorComponent::ActorComponent(actor)
{
}

Behavior::~Behavior()
{
}

void Behavior::begin()
{
}

void Behavior::update() 
{
}

void Behavior::end() 
{
}