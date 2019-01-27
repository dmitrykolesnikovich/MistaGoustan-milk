#include "SceneManager.h"

#include "scene/Scene.h"

#include "events/EventQueue.h"
#include "events/GameEvents.h"

#include "SceneLoader.h"

milk::SceneManager::SceneManager(EventQueue& eventQueue, SceneLoader& sceneLoader)
        : eventQueue_(eventQueue), sceneLoader_(sceneLoader), scene_(nullptr) {
}

milk::SceneManager::~SceneManager() = default;

void milk::SceneManager::loadScene(const std::string& scene) {
    if (scene_ != nullptr)
        scene_->end();

    eventQueue_.pushEvent<SceneChangedEvent>(scene);
    sceneToLoad_ = scene;
}

void milk::SceneManager::update() {
    if (!sceneToLoad_.empty()) {
        if (scene_ != nullptr)
            scene_.reset();

        scene_ = sceneLoader_.load(sceneToLoad_);
        sceneToLoad_.erase();
    }

    if (scene_ != nullptr)
        scene_->syncActorLists();
}

void milk::SceneManager::shutDown() {
    if (scene_ != nullptr)
        scene_->end();
}

milk::Scene* milk::SceneManager::currentScene() const {
    return scene_.get();
}
