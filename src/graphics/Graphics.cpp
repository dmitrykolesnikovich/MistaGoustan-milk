#include "Graphics.h"

#include <cmath>

#include "SDL.h"

#include "Animator.h"
#include "Sprite.h"
#include "Texture.h"

#include "scene/Actor.h"
#include "scene/Scene.h"

#include "events/GameEvents.h"

milk::Graphics::Graphics(SDL_Renderer& renderer, const std::string& rootDir)
        : sdlRenderer_(renderer), textureLoader(renderer, rootDir) {
}

void milk::Graphics::handleEvent(milk::GameEvent& gameEvent) {
    switch (gameEvent.type()) {
        case GameEventType::ACTOR_SPAWNED: {
            auto& spawnedEvent = dynamic_cast<ActorSpawnedEvent&>(gameEvent);
            onActorSpawned(spawnedEvent.actor());
        }
            break;
        case GameEventType::ACTOR_DETROYED: {
            auto& destroyedEvent = dynamic_cast<ActorDestroyedEvent&>(gameEvent);
            onActorDestroyed(destroyedEvent.actor());
        }
            break;
        case GameEventType::SCENE_LOADED: {
            textureLoader.unload();
        }
            break;
        default:
            break;
    }
}

void milk::Graphics::render(milk::Scene& scene) {
    scene.camera().update();
    renderTilemap(scene.tilemap(), scene.camera());
    renderActors(scene.camera());
}

void milk::Graphics::onActorSpawned(milk::Actor& actor) {
    auto sprite = actor.getComponent<Sprite>();

    if (sprite == nullptr)
        return;

    sprite->load(textureLoader);

    spritesByActorId_.insert(std::make_pair(actor.id(), sprite));

    auto anim = actor.getComponent<Animator>();

    if (anim != nullptr)
        anim->init();
}

void milk::Graphics::onActorDestroyed(Actor& actor) {
    if (spritesByActorId_.find(actor.id()) != spritesByActorId_.end())
        spritesByActorId_.erase(actor.id());
}

void milk::Graphics::renderTilemap(const Tilemap& tilemap, const Camera& camera) {
    for (auto& layer : tilemap.layers) {
        for (auto& tile : layer->tiles) {
            SDL_Rect destinationRect;
            destinationRect.x = tile->x - camera.position().x;
            destinationRect.y = tile->y - camera.position().y;
            destinationRect.w = tile->type.sourceRect.w;
            destinationRect.h = tile->type.sourceRect.h;

            SDL_RenderCopyEx(&sdlRenderer_, tilemap.texture->get(), &tile->type.sourceRect, &destinationRect, 0,
                             nullptr, SDL_FLIP_NONE);
        }
    }
}

void milk::Graphics::renderActors(const Camera& camera) {
    for (auto it : spritesByActorId_) {
        Animator* animator = it.second->actor().getComponent<Animator>();

        if (animator != nullptr)
            animator->update();

        auto texture = it.second->texture();
        auto sourceRect = it.second->sourceRect();
        auto destinationRect = it.second->destinationRect();
        destinationRect.x -= camera.position().x;
        destinationRect.y -= camera.position().y;

        SDL_RenderCopyEx(&sdlRenderer_, texture->get(), &sourceRect, &destinationRect, 0, nullptr,
                         it.second->rendererFlip());
    }
}
