#include "Actor.h"

#include "ActorComponent.h"

milk::Actor::Actor(int id, const std::string& name, const Vector2d& position)
        : id_(id), name_(name), position_(position), componentBitmask_(0) {
}

int milk::Actor::id() const {
    return id_;
}

std::string milk::Actor::name() const {
    return name_;
}

milk::Vector2d milk::Actor::position() const {
    return position_;
}

void milk::Actor::position(float x, float y) {
    position_.x = x;
    position_.y = y;
}
