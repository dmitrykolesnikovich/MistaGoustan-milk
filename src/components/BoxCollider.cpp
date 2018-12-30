#include "BoxCollider.h"

#include "../core/Actor.h"

const ComponentType BoxCollider::type = BOX_COLLIDER;

BoxCollider::BoxCollider(Actor& actor)
	: ActorComponent::ActorComponent(actor)
	, alignment_(Alignment::TOP_LEFT)
	, offset_(0, 0)
{
	updateBBox();
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::center()
{
	alignment_ = Alignment::CENTER_ORIGIN;

	updateBBox();
}

void BoxCollider::updateBBox()
{
	Vector2d actorPosition = actor_.position();

	switch (alignment_) 
	{
	case Alignment::TOP_LEFT:
		rect_.x = actorPosition.x + offset_.x;
		rect_.y = actorPosition.y + offset_.y;
		break;
	case Alignment::CENTER_ORIGIN:
		rect_.x = actorPosition.x - (rect_.w / 2) + offset_.x;
		rect_.y = actorPosition.y - (rect_.h / 2) + offset_.y;
		break;
	}
}

SDL_Rect BoxCollider::rect() const
{
	return rect_;
}

void BoxCollider::width(int width)
{
	rect_.w = width;
}

void BoxCollider::height(int height)
{
	rect_.h = height;
}

void BoxCollider::offset(int x, int y)
{
	offset_.x = x;
	offset_.y = y;
}

bool BoxCollider::overlaps(SDL_Rect otherRect) const
{
	return SDL_HasIntersection(&rect_, &otherRect);
}

bool BoxCollider::overlaps(SDL_Rect otherRect, SDL_Rect* result) const
{
	return SDL_IntersectRect(&rect_, &otherRect, result);
}
