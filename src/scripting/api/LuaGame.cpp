#include "LuaGame.h"

#include "core/Game.h"

#include "utilities/SceneManager.h"

namespace milk {
    namespace lua {
        namespace game {
            Window& window(Game& game) {
                return game.window();
            }

            Scene& scene(Game& game) {
                return *game.sceneManager().currentScene();
            }

            void loadScene(Game& game, const std::string& name) {
                game.loadScene(name);
            }
        }
    }
}