#include "Sprite.h"

#include "../utilities/ResourceManager.h"

const ComponentType Sprite::type = SPRITE;

Sprite::Sprite(Actor& actor)
	: ActorComponent::ActorComponent(actor)
{
}

Sprite::~Sprite()
{
}

void Sprite::load(ResourceManager& resourceManager)
{
	texture_ = resourceManager.loadTexture(textureName_);
}

void Sprite::textureName(const std::string& name)
{
	textureName_ = name;
}

Texture* Sprite::texture() const
{
	return texture_;
}

void Sprite::sourceRect(int x, int y, int width, int height)
{
	sourceRect_.x = x;
	sourceRect_.y = y;
	sourceRect_.w = width;
	sourceRect_.h = height;
}

void Sprite::sourceRect(SDL_Rect rect)
{
	sourceRect_.x = rect.x;
	sourceRect_.y = rect.y;
	sourceRect_.w = rect.w;
	sourceRect_.h = rect.h;
}

SDL_Rect Sprite::sourceRect() const
{
	return sourceRect_;
}
