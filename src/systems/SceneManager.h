#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H

#include <memory>

#include "core/Scene.h"

class EventQueue;
class GameEvent;
class SceneLoader;

class SceneManager
{
public:
    explicit SceneManager(EventQueue& eventQueue, SceneLoader& sceneLoader);

    void update();

    void loadScene(const std::string& scene);

    void shutDown();

    Scene* currentScene() const;

private:
    EventQueue& eventQueue_;
    SceneLoader& sceneLoader_;

    std::unique_ptr<Scene> scene_;
    std::string sceneToLoad_;
};

#endif
