#include "BoxCollider.h"

#include "../core/Actor.h"

const ComponentType BoxCollider::type = BOX_COLLIDER;

BoxCollider::BoxCollider(Actor& actor)
	: ActorComponent::ActorComponent(actor)
{
	rect_.x = actor_.position().x;
	rect_.y = actor_.position().y;
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::updateBBox()
{
	rect_.x = actor_.position().x;
	rect_.y = actor_.position().y;
}

SDL_Rect BoxCollider::rect() const
{
	return rect_;
}

int BoxCollider::width() const
{
	return rect_.w;
}

int BoxCollider::height() const
{
	return rect_.h;
}

void BoxCollider::width(int width)
{
	rect_.w = width;
}

void BoxCollider::height(int height)
{
	rect_.h = height;
}

bool BoxCollider::overlaps(SDL_Rect otherRect) const
{
	return SDL_HasIntersection(&rect_, &otherRect);
}

bool BoxCollider::overlaps(SDL_Rect otherRect, SDL_Rect* result) const
{
	return SDL_IntersectRect(&rect_, &otherRect, result);
}
