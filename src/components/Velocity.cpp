#include "Velocity.h"

const ComponentType Velocity::type = VELOCITY;

Velocity::Velocity(Actor& actor)
	: ActorComponent::ActorComponent(actor)
{
	value_ = Vector2d(0, 0);
}

void Velocity::value(float x, float y)
{
	value_.x = x;
	value_.y = y;
}

void Velocity::value(Vector2d velocity)
{
	value_.x = velocity.x;
	value_.y = velocity.y;
}

Vector2d Velocity::value() const
{
	return value_;
}
