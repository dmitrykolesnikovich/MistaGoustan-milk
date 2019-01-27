#include "LuaScene.h"

#include "core/Scene.h"

namespace milk {
    namespace lua {
        namespace scene {
            void setCameraTarget(Scene& scene, Actor& actor) {
                scene.camera().setTarget(&actor);
            }
        }
    }
}