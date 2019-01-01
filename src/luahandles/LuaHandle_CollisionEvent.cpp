#include "LuaHandle_CollisionEvent.h"

LuaHandle_CollisionEvent::LuaHandle_CollisionEvent(ActorCollisionEvent& collisionEvent)
	: collisionEvent_(collisionEvent)
{
}

LuaHandle_BoxCollider LuaHandle_CollisionEvent::other()
{
	return LuaHandle_BoxCollider(collisionEvent_.collider());
}
