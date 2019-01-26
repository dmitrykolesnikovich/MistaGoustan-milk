#include "LuaHandle_BoxCollider.h"

LuaHandle_BoxCollider::LuaHandle_BoxCollider(BoxCollider& collider)
        : collider_(collider) {
}

Actor& LuaHandle_BoxCollider::actor() const {
    return collider_.actor();
}
