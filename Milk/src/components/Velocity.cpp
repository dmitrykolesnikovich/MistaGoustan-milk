#include "Velocity.h"

const ComponentType Velocity::type = VELOCITY;

Velocity::Velocity(Actor& actor)
	: ActorComponent::ActorComponent(actor)
{
	value_ = Vector2d(0, 0);
}

Velocity::~Velocity()
{
}

void Velocity::setVelocity(float x, float y)
{
	value_.x = x;
	value_.y = y;
}

void Velocity::setVelocity(Vector2d velocity)
{
	value_.x = velocity.x;
	value_.y = velocity.y;
}

Vector2d Velocity::getVelocity() const
{
	return value_;
}
