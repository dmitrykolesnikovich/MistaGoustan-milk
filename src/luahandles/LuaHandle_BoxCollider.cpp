#include "LuaHandle_BoxCollider.h"

LuaHandle_BoxCollider::LuaHandle_BoxCollider(BoxCollider& collider)
	: collider_(collider)
{
}

LuaHandle_Actor LuaHandle_BoxCollider::actor() const
{
	return LuaHandle_Actor(collider_.actor());
}
