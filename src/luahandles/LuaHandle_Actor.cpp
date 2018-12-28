#include "LuaHandle_Actor.h"

#include "../core/Actor.h"
#include "../components/Velocity.h"

#include <iostream>

void LuaHandle_Actor::move(Actor& actor, float x, float y)
{
	auto velCmp = actor.getComponent<Velocity>();
	if (velCmp == nullptr)
		return;

	velCmp->value(x, y);
}
