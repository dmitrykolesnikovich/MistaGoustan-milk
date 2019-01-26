#ifndef _LUACOLLISIONEVENT_H
#define _LUACOLLISIONEVENT_H

class Actor;
class ActorCollisionEvent;

namespace mlk {
    namespace lua {
        namespace collision_event {
            Actor& other(ActorCollisionEvent& collisionEvent);
        }
    }
}


#endif
