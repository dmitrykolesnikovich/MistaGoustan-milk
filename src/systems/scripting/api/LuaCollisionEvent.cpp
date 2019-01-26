#include "LuaCollisionEvent.h"

#include "systems/physics/BoxCollider.h"
#include "systems/events/GameEvents.h"

namespace mlk {
    namespace lua {
        namespace collision_event {
            Actor& other(ActorCollisionEvent& collisionEvent) {
                return collisionEvent.collider().actor();
            }
        }
    }
}