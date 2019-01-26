#include "Actor.h"

#include "ActorComponent.h"

Actor::Actor(int id, const std::string& name, const Vector2d& position)
        : id_(id), name_(name), position_(position), componentBitmask_(0) {
}

int Actor::id() const {
    return id_;
}

std::string Actor::name() const {
    return name_;
}

Vector2d Actor::position() const {
    return position_;
}

void Actor::position(float x, float y) {
    position_.x = x;
    position_.y = y;
}
