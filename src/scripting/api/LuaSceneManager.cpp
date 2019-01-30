#include "LuaSceneManager.h"

#include "scene/Scene.h"
#include "scene/SceneManager.h"

namespace milk
{
    namespace lua
    {
        namespace scene_manager
        {
            Scene& current(SceneManager& sceneManager)
            {
                auto scene = sceneManager.currentScene();
                return *scene;
            }

            void loadScene(SceneManager& sceneManager, const std::string& sceneName)
            {
                sceneManager.loadScene(sceneName);
            }
        }
    }
}