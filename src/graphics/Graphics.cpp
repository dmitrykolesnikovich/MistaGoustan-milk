#include "Graphics.h"

#include <cmath>

#include "SDL.h"

#include "Animator.h"
#include "Sprite.h"
#include "Texture.h"

#include "events/GameEvents.h"
#include "scene/Actor.h"
#include "scene/Scene.h"
#include "window/Renderer.h"

milk::Graphics::Graphics(Renderer& renderer, AssetCache<Texture>& textureCache)
        : renderer_(renderer),
          textureCache_(textureCache)
{
}

void milk::Graphics::handleEvent(milk::GameEvent& gameEvent)
{
    switch (gameEvent.type())
    {
        case GameEventType::ACTOR_SPAWNED:
        {
            auto& spawnedEvent = dynamic_cast<ActorSpawnedEvent&>(gameEvent);
            onActorSpawned(spawnedEvent.actor());
        }
            break;
        case GameEventType::ACTOR_DETROYED:
        {
            auto& destroyedEvent = dynamic_cast<ActorDestroyedEvent&>(gameEvent);
            onActorDestroyed(destroyedEvent.actor());
        }
            break;
        case GameEventType::SCENE_LOADED:
        {
            textureCache_.invalidate();
        }
            break;
        default:
            break;
    }
}

void milk::Graphics::render(milk::Scene& scene)
{
    renderTilemap(scene.tilemap(), scene.camera());
    renderActors(scene.camera());
}

void milk::Graphics::onActorSpawned(milk::Actor& actor)
{
    auto sprite = actor.getComponent<Sprite>();

    if (sprite == nullptr)
        return;

    sprite->load(textureCache_);

    spritesByActorId_.insert(std::make_pair(actor.id(), sprite));

    auto anim = actor.getComponent<Animator>();

    if (anim != nullptr)
        anim->init();
}

void milk::Graphics::onActorDestroyed(Actor& actor)
{
    if (spritesByActorId_.find(actor.id()) != spritesByActorId_.end())
        spritesByActorId_.erase(actor.id());
}

void milk::Graphics::renderTilemap(const Tilemap& tilemap, const Camera& camera)
{
    for (auto& layer : tilemap.layers)
    {
        for (auto& tile : layer->tiles)
        {
            Rectangle destinationRect;
            destinationRect.x = tile->x - camera.position().x;
            destinationRect.y = tile->y - camera.position().y;
            destinationRect.width = tile->type.sourceRect.width;
            destinationRect.height = tile->type.sourceRect.height;

            renderer_.draw(*tilemap.texture, tile->type.sourceRect, destinationRect, SDL_FLIP_NONE);
        }
    }
}

void milk::Graphics::renderActors(const Camera& camera)
{
    for (auto it : spritesByActorId_)
    {
        Animator* animator = it.second->actor().getComponent<Animator>();

        if (animator != nullptr)
            animator->update();

        auto texture = it.second->texture();
        auto sourceRect = it.second->sourceRect();
        auto destinationRect = it.second->destinationRect();
        destinationRect.x -= camera.position().x;
        destinationRect.y -= camera.position().y;

        renderer_.draw(*texture, sourceRect, destinationRect, it.second->rendererFlip());
    }
}
