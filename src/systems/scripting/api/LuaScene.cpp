#include "LuaScene.h"

#include "core/Scene.h"

namespace mlk {
    namespace lua {
        namespace scene {
            void setCameraTarget(Scene& scene, Actor& actor) {
                scene.camera().setTarget(&actor);
            }
        }
    }
}