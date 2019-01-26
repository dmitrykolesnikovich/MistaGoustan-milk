#include "LuaCollisionEvent.h"

#include "components/BoxCollider.h"
#include "systems/GameEvents.h"

namespace mlk {
    namespace lua {
        namespace collision_event {
            Actor& other(ActorCollisionEvent& collisionEvent) {
                return collisionEvent.collider().actor();
            }
        }
    }
}