#include "Renderer.h"

#include <SDL.h>

#include "../components/Sprite.h"
#include "../core/Scene.h"
#include "../utilities/Texture.h"

Renderer::Renderer(SDL_Renderer& renderer)
	: _renderer(renderer)
{
}

void Renderer::update(Scene& scene)
{
	auto& actorsById = scene.getAllActors();

	for (auto& it : actorsById) 
	{
		auto actor = it.second.get();
		auto sprite = actor->getComponent<Sprite>();

		if (sprite == nullptr)
			continue;

		auto actorPosition = actor->getPosition();
		auto texture = sprite->getTexture();
		auto sourceRect = sprite->getSourceRect();

		SDL_Rect destination;
		destination.x = actorPosition.x;
		destination.y = actorPosition.y;
		destination.w = sourceRect.w;
		destination.h = sourceRect.h;

		SDL_RenderCopyEx(&_renderer, texture->get(), &sourceRect, &destination, 0, nullptr, SDL_FLIP_NONE);
	}
}
