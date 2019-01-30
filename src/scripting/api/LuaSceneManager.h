#ifndef MILK_LUASCENEMANAGER_H
#define MILK_LUASCENEMANAGER_H

#include <string>

namespace milk
{
    class Scene;
    class SceneManager;

    namespace lua
    {
        namespace scene_manager
        {
            Scene& current(SceneManager& sceneManager);

            void loadScene(SceneManager& sceneManager, const std::string& sceneName);
        }
    }
}

#endif
