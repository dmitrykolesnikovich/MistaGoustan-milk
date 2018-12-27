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

void Sprite::setTextureName(const std::string& name)
{
	textureName_ = name;
}

Texture* Sprite::getTexture() const
{
	return texture_;
}

void Sprite::setSourceRect(int x, int y, int width, int height)
{
	sourceRect_.x = x;
	sourceRect_.y = y;
	sourceRect_.w = width;
	sourceRect_.h = height;
}

void Sprite::setSourceRect(SDL_Rect rect)
{
	sourceRect_.x = rect.x;
	sourceRect_.y = rect.y;
	sourceRect_.w = rect.w;
	sourceRect_.h = rect.h;
}

SDL_Rect Sprite::getSourceRect() const
{
	return sourceRect_;
}