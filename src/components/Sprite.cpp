#include "Sprite.h"

#include "../core/Actor.h"
#include "../math/Vector2d.h"
#include "../utilities/ResourceManager.h"

const ComponentType Sprite::type = SPRITE;

Sprite::Sprite(Actor& actor)
	: ActorComponent::ActorComponent(actor)
	, alignment_(Alignment::TOP_LEFT)
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

void Sprite::center()
{
	alignment_ = Alignment::CENTER_ORIGIN;
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

SDL_Rect Sprite::destinationRect() const
{
	Vector2d actorPosition = actor_.position();

	SDL_Rect destinationRect;
	destinationRect.w = sourceRect_.w;
	destinationRect.h = sourceRect_.h;

	switch (alignment_)
	{
	case Alignment::TOP_LEFT:
		destinationRect.x = std::floor(actorPosition.x);
		destinationRect.y = std::floor(actorPosition.y);
		break;
	case Alignment::CENTER_ORIGIN:
		destinationRect.x = std::floor(actorPosition.x) - (sourceRect_.w / 2);
		destinationRect.y = std::floor(actorPosition.y) - (sourceRect_.h / 2);
		break;
	}

	return destinationRect;
}
