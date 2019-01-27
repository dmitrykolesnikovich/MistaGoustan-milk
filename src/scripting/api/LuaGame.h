#ifndef MILK_LUA_GAME_H
#define MILK_LUA_GAME_H

#include <string>
namespace milk {
    class Game;
    class Scene;
    class Window;

    namespace lua {
        namespace game {
            Window& window(Game& game);

            Scene& scene(Game& game);

            void loadScene(Game& game, const std::string& name);
        }
    }
}

#endif
