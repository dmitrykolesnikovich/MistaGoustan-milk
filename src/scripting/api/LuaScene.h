#ifndef _LUASCENE_H
#define _LUASCENE_H

namespace milk {
    class Actor;
    class Scene;

    namespace lua {
        namespace scene {
            void setCameraTarget(Scene& scene, Actor& actor);
        }
    }
}

#endif