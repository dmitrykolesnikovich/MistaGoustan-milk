#ifndef MILK_SCENE_MANAGER_H
#define MILK_SCENE_MANAGER_H

#define MILK_NULL_SCENE "ABSOLUTELY_NO_GD_SCENE"

#include <memory>
#include <string>

namespace milk
{
    class EventQueue;
    class GameEvent;
    class Scene;
    class SceneLoader;

    class SceneManager
    {
    public:
        explicit SceneManager(EventQueue& eventQueue, SceneLoader& sceneLoader);

        ~SceneManager();

        void update();

        void loadScene(const std::string& scene);

        Scene* currentScene() const;

    private:
        EventQueue& eventQueue_;
        SceneLoader& sceneLoader_;

        std::unique_ptr<Scene> scene_;
        std::string sceneToLoad_;
    };
}

#endif
