#include "BoxCollider.h"

#include "../core/Actor.h"

const ComponentType BoxCollider::type = BOX_COLLIDER;

BoxCollider::BoxCollider(Actor& actor)
	: ActorComponent::ActorComponent(actor)
	, alignment_(Alignment::TOP_LEFT)
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
		rect_.x = actorPosition.x;
		rect_.y = actorPosition.y;
		break;
	case Alignment::CENTER_ORIGIN:
		rect_.x = actorPosition.x - (rect_.w / 2);;
		rect_.y = actorPosition.y - (rect_.h / 2);
		break;
	}
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
