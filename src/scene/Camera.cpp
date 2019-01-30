#include "Camera.h"

#include "scene/Actor.h"
#include "scene/Scene.h"

milk::Camera::Camera(milk::Scene& scene, unsigned int width, unsigned int height)
        : scene_(scene),
          target_(nullptr)
{

    camRect_.x = 0;
    camRect_.y = 0;
    camRect_.w = width;
    camRect_.h = height;
}

void milk::Camera::position(float x, float y)
{
    camRect_.x = (int)std::floor(x);
    camRect_.y = (int)std::floor(y);
}

milk::Vector2d milk::Camera::position() const
{
    return {(float)camRect_.x, (float)camRect_.y};
}

void milk::Camera::setTarget(Actor* actor)
{
    target_ = actor;
}

void milk::Camera::update()
{
    followTarget();
    clampCameraToSceneBounds();
}

void milk::Camera::followTarget()
{
    if (target_ != nullptr)
    {
        camRect_.x = (int)std::floor(target_->position().x - camRect_.w * 0.5f);
        camRect_.y = (int)std::floor(target_->position().y - camRect_.h * 0.5f);
    }
}

void milk::Camera::clampCameraToSceneBounds()
{
    if (camRect_.x < scene_.bounds().x)
        camRect_.x = scene_.bounds().x;
    else if ((camRect_.x + camRect_.w) > scene_.bounds().width)
        camRect_.x = scene_.bounds().width - camRect_.w;

    if (camRect_.y < scene_.bounds().y)
        camRect_.y = scene_.bounds().y;
    else if ((camRect_.y + camRect_.h) > scene_.bounds().height)
        camRect_.y = scene_.bounds().height - camRect_.h;
}
