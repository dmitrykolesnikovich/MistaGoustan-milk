#include "SceneManager.h"

#include "EventQueue.h"
#include "GameEvents.h"
#include "utilities/SceneLoader.h"

SceneManager::SceneManager(EventQueue& eventQueue, SceneLoader& sceneLoader)
    : eventQueue_(eventQueue)
    , sceneLoader_(sceneLoader)
    , scene_(nullptr)
{
}

void SceneManager::loadScene(const std::string& scene)
{
    if (scene_ != nullptr)
        scene_->end();

    eventQueue_.pushEvent<SceneChangedEvent>(scene);
    sceneToLoad_ = scene;
}

void SceneManager::update()
{
    if (!sceneToLoad_.empty())
    {
        if (scene_ != nullptr)
            scene_.reset();

        scene_ = sceneLoader_.load(sceneToLoad_);
        sceneToLoad_.erase();
    }

    if (scene_ != nullptr)
        scene_->update();
}

void SceneManager::shutDown()
{
    if (scene_ != nullptr)
        scene_->end();
}

Scene* SceneManager::currentScene() const
{
    return scene_.get();
}
