#include "LuaCollisionEvent.h"

#include "physics/BoxCollider.h"
#include "events/GameEvents.h"

namespace milk
{
    namespace lua
    {
        namespace collision_event
        {
            Actor& other(ActorCollisionEvent& collisionEvent)
            {
                return collisionEvent.collider().actor();
            }
        }
    }
}