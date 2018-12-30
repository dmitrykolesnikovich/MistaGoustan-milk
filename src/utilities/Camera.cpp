#include "Camera.h"

#include "../core/Actor.h"

Camera::Camera(unsigned int width, unsigned int height)
	: target_(nullptr)
{
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = width;
	rect_.h = height;
}

void Camera::position(float x, float y)
{
	rect_.x = std::floor(x);
	rect_.y = std::floor(y);
}

Vector2d Camera::position() const
{
	return Vector2d(rect_.x, rect_.y);
}

void Camera::setTarget(Actor* actor)
{
	target_ = actor;
}

void Camera::update()
{
	if (target_ != nullptr)
	{
		rect_.x = std::floor(target_->position().x - rect_.w  * 0.5f);
		rect_.y = std::floor(target_->position().y - rect_.h * 0.5f);
	}
}
