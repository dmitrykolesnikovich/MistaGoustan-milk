#include "LuaGame.h"

#include "game/Game.h"

#include "scene/SceneManager.h"

namespace milk
{
    namespace lua
    {
        namespace game
        {
            Window& window(Game& game)
            {
                return game.window();
            }

            Scene& scene(Game& game)
            {
                return *game.sceneManager().currentScene();
            }

            void loadScene(Game& game, const std::string& name)
            {
                game.loadScene(name);
            }
        }
    }
}