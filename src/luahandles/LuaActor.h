#ifndef _LUA_ACTOR_H
#define _LUA_ACTOR_H

#include <string>

class Actor;

namespace mlk {
    namespace lua {
        namespace actor {
            std::string name(Actor& actor);

            void setAsCameraTarget(Actor& actor);

            void move(Actor& actor, float x, float y);

            void setAnimation(Actor& actor, const std::string& name);

            void flipX(Actor& actor);

            void flipY(Actor& actor);
        }
    }
}


#endif
