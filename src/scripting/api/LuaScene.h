#ifndef _LUASCENE_H
#define _LUASCENE_H

class Actor;
class Scene;

namespace mlk {
    namespace lua {
        namespace scene {
            void setCameraTarget(Scene& scene, Actor& actor);
        }
    }
}

#endif