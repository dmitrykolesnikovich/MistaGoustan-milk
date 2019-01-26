#ifndef _LUA_HANDLE_BOX_COLLIDER_
#define _LUA_HANDLE_BOX_COLLIDER_

#include "components/BoxCollider.h"

class LuaHandle_BoxCollider {
public:
    explicit LuaHandle_BoxCollider(BoxCollider& collider);

    Actor& actor() const;

private:
    BoxCollider& collider_;
};

#endif
