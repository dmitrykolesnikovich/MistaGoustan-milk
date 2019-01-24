#ifndef _LUA_HANDLE_COLLISION_EVENT_
#define _LUA_HANDLE_COLLISION_EVENT_

#include "LuaHandle_BoxCollider.h"

class ActorCollisionEvent;

class LuaHandle_CollisionEvent {
public:
    explicit LuaHandle_CollisionEvent(ActorCollisionEvent& collisionEvent);

    LuaHandle_BoxCollider other();

private:
    ActorCollisionEvent& collisionEvent_;
};

#endif
