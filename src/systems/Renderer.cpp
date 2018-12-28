#include "Renderer.h"

#include "SDL.h"

#include "../components/Animator.h"
#include "../components/Sprite.h"
#include "../core/Scene.h"

#include "../utilities/Texture.h"

Renderer::Renderer(SDL_Renderer* renderer, ResourceManager& resourceManager)
	: sdlRenderer_(renderer), resourceManager_(resourceManager)
{
}

void Renderer::onActorAdded(Actor& actor)
{
	Sprite* sprite = actor.getComponent<Sprite>();
	if (sprite != nullptr) 
	{
		sprite->load(resourceManager_);
		spritesByActorId_.insert(std::make_pair(actor.id(), sprite));

		auto anim = actor.getComponent<Animator>();
		if (anim != nullptr)
			anim->init();
	}
}

void Renderer::onActorDestroyed(Actor& actor)
{
	if (spritesByActorId_.find(actor.id()) != spritesByActorId_.end()) 
	{
		spritesByActorId_.erase(actor.id());
	}
}

void Renderer::onActorModified(Actor& actor)
{
}

void Renderer::render(Tilemap& tilemap)
{
	for (auto& layer : tilemap.layers)
	{
		for (auto& tile : layer->tiles)
		{
			SDL_Rect dst;
			dst.x = tile->x;
			dst.y = tile->y;
			dst.w = tile->type.rect.w;
			dst.h = tile->type.rect.h;

			SDL_RenderCopyEx(sdlRenderer_, tilemap.texture->get(), &tile->type.rect, &dst, 0, nullptr, SDL_FLIP_NONE);
		}
	}

	for (auto it : spritesByActorId_) 
	{
		Animator* animator = it.second->actor().getComponent<Animator>();
		if (animator != nullptr)
			animator->update();

		auto actorPosition = it.second->actor().position();
		auto texture = it.second->texture();
		auto sourceRect = it.second->getSourceRect();

		SDL_Rect destination;
		destination.x = actorPosition.x;
		destination.y = actorPosition.y;
		destination.w = sourceRect.w;
		destination.h = sourceRect.h;

		SDL_RenderCopyEx(sdlRenderer_, texture->get(), &sourceRect, &destination, 0, nullptr, SDL_FLIP_NONE);
	}
}
