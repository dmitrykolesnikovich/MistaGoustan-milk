#include "Renderer.h"

#include "SDL.h"

#include <cmath>

#include "../components/Animator.h"
#include "../components/Sprite.h"
#include "../core/Scene.h"

#include "../utilities/Texture.h"

Renderer::Renderer(SDL_Renderer* renderer, ResourceManager& resourceManager)
	: sdlRenderer_(renderer)
	, resourceManager_(resourceManager)
{
}

void Renderer::onActorAdded(Actor& actor)
{
	Sprite* sprite = actor.getComponent<Sprite>();

	if (sprite == nullptr)
		return;

	sprite->load(resourceManager_);
	spritesByActorId_.insert(std::make_pair(actor.id(), sprite));

	auto anim = actor.getComponent<Animator>();

	if (anim != nullptr)
		anim->init();
}

void Renderer::onActorDestroyed(Actor& actor)
{
	if (spritesByActorId_.find(actor.id()) != spritesByActorId_.end()) 	
		spritesByActorId_.erase(actor.id());	
}

void Renderer::render(Tilemap& tilemap)
{
	renderTilemap(tilemap);
	renderActors();
}

void Renderer::renderTilemap(const Tilemap& tilemap)
{
	for (auto& layer : tilemap.layers)
	{
		for (auto& tile : layer->tiles)
		{
			SDL_Rect destinationRect;
			destinationRect.x = tile->x;
			destinationRect.y = tile->y;
			destinationRect.w = tile->type.sourceRect.w;
			destinationRect.h = tile->type.sourceRect.h;

			SDL_RenderCopyEx(sdlRenderer_, tilemap.texture->get(), &tile->type.sourceRect, &destinationRect, 0, nullptr, SDL_FLIP_NONE);
		}
	}
}

void Renderer::renderActors()
{
	for (auto it : spritesByActorId_)
	{
		Animator* animator = it.second->actor().getComponent<Animator>();

		if (animator != nullptr)
			animator->update();

		auto actorPosition = it.second->actor().position();
		auto texture = it.second->texture();
		auto sourceRect = it.second->sourceRect();

		SDL_Rect destinationRect;
		destinationRect.x = std::floor(actorPosition.x) - (sourceRect.w / 2);
		destinationRect.y = std::floor(actorPosition.y) - (sourceRect.h / 2);
		destinationRect.w = sourceRect.w;
		destinationRect.h = sourceRect.h;

		SDL_RenderCopyEx(sdlRenderer_, texture->get(), &sourceRect, &destinationRect, 0, nullptr, SDL_FLIP_NONE);
	}
}
