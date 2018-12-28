#include "LuaHandle_Actor.h"

#include "../components/Velocity.h"
#include "../core/Actor.h"

LuaHandle_Actor::LuaHandle_Actor(Actor& actor)
	: actor_(actor)
{
}

void LuaHandle_Actor::move(float x, float y)
{
	auto velocity = actor_.getComponent<Velocity>();
	if (velocity == nullptr)
		return;

	velocity->value(x, y);
}
