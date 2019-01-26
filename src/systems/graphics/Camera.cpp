#include "Camera.h"

#include "core/Actor.h"
#include "core/Scene.h"

Camera::Camera(Scene& scene, unsigned int width, unsigned int height)
        : scene_(scene), target_(nullptr) {
    camRect_.x = 0;
    camRect_.y = 0;
    camRect_.w = width;
    camRect_.h = height;
}

void Camera::position(float x, float y) {
    camRect_.x = (int)std::floor(x);
    camRect_.y = (int)std::floor(y);
}

Vector2d Camera::position() const {
    return {(float)camRect_.x, (float)camRect_.y};
}

void Camera::setTarget(Actor* actor) {
    target_ = actor;
}

void Camera::update() {
    followTarget();
    clampCameraToSceneBounds();
}

void Camera::followTarget() {
    if (target_ != nullptr) {
        camRect_.x = (int)std::floor(target_->position().x - camRect_.w * 0.5f);
        camRect_.y = (int)std::floor(target_->position().y - camRect_.h * 0.5f);
    }
}

void Camera::clampCameraToSceneBounds() {
    if (camRect_.x < scene_.bounds().x)
        camRect_.x = scene_.bounds().x;
    else if ((camRect_.x + camRect_.w) > scene_.bounds().w)
        camRect_.x = scene_.bounds().w - camRect_.w;

    if (camRect_.y < scene_.bounds().y)
        camRect_.y = scene_.bounds().y;
    else if ((camRect_.y + camRect_.h) > scene_.bounds().h)
        camRect_.y = scene_.bounds().h - camRect_.h;
}
