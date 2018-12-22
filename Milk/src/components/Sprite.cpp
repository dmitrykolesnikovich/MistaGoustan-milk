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
	_texture = resourceManager.loadTexture(_textureName);
}

void Sprite::setTextureName(const std::string& name)
{
	_textureName = name;
}

Texture* Sprite::getTexture() const
{
	return _texture;
}

void Sprite::setSourceRect(int x, int y, int width, int height)
{
	_sourceRect.x = x;
	_sourceRect.y = y;
	_sourceRect.w = width;
	_sourceRect.h = height;
}

void Sprite::setSourceRect(SDL_Rect rect)
{
	_sourceRect.x = rect.x;
	_sourceRect.y = rect.y;
	_sourceRect.w = rect.w;
	_sourceRect.h = rect.h;
}

SDL_Rect Sprite::getSourceRect() const
{
	return _sourceRect;
}
