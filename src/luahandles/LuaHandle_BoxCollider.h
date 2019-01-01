#ifndef _LUA_HANDLE_BOX_COLLIDER_
#define _LUA_HANDLE_BOX_COLLIDER_

#include "../components/BoxCollider.h"

#include "LuaHandle_Actor.h"

class LuaHandle_BoxCollider
{
public:
	LuaHandle_BoxCollider(BoxCollider& collider);

	LuaHandle_Actor actor() const;

private:
	BoxCollider& collider_;
};

#endif
