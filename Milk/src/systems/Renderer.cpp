#include "Renderer.h"

#include <SDL.h>

#include "../components/Sprite.h"
#include "../core/Scene.h"
#include "../utilities/Texture.h"

Renderer::Renderer(SDL_Renderer& renderer, ResourceManager& resourceManager)
	: sdlRenderer_(renderer), resourceManager_(resourceManager)
{
}

void Renderer::onActorAdded(Actor& actor)
{
	Sprite* sprite = actor.getComponent<Sprite>();
	if (sprite != nullptr) 
	{
		sprite->load(resourceManager_);
		spritesByActorId_.insert(std::make_pair(actor.getId(), sprite));
	}
}

void Renderer::onActorDestroyed(Actor & actor)
{
}

void Renderer::onActorModified(Actor & actor)
{
}

void Renderer::update(Scene& scene)
{
	for (auto it : spritesByActorId_) 
	{
		auto actorPosition = it.second->getActor().getPosition();
		auto texture = it.second->getTexture();
		auto sourceRect = it.second->getSourceRect();

		SDL_Rect destination;
		destination.x = actorPosition.x;
		destination.y = actorPosition.y;
		destination.w = sourceRect.w;
		destination.h = sourceRect.h;

		SDL_RenderCopyEx(&sdlRenderer_, texture->get(), &sourceRect, &destination, 0, nullptr, SDL_FLIP_NONE);
	}
}
