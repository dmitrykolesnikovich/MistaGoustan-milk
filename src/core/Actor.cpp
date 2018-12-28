#include "Actor.h"

Actor::Actor(Scene& scene)
	: scene_(scene)
{
	componentBitmask_ = 0;
}

Actor::~Actor()
{
}

int Actor::id() const
{
	return id_;
}

std::string Actor::getName() const
{
	return name_;
}

Vector2d Actor::position() const
{
	return position_;
}

void Actor::position(float x, float y)
{
	position_.x = x;
	position_.y = y;
}

void Actor::position(Vector2d position)
{
	position_.x = position.x;
	position_.y = position.y;
}
