#ifndef _LUAGAME_H
#define _LUAGAME_H

#include <string>

class Game;
class Scene;
class Window;

namespace mlk {
    namespace lua {
        namespace game {
            Window& window(Game& game);

            Scene& scene(Game& game);

            void loadScene(Game& game, const std::string& name);
        }
    }
}

#endif
