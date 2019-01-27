#include "BoxCollider.h"

#include "SpatialPartitionGrid.h"

#include "core/Actor.h"

const milk::ComponentType milk::BoxCollider::type = BOX_COLLIDER;

milk::BoxCollider::BoxCollider(Actor& actor)
        : ActorComponent::ActorComponent(actor), origin_(Alignment::TOP_LEFT), offset_(0, 0), grid_(nullptr),
          next_(nullptr), prev_(nullptr) {

    updateBBox();
}

void milk::BoxCollider::init(SpatialPartitionGrid* grid) {
    grid_ = grid;

    updateBBox();
}

void milk::BoxCollider::center() {
    origin_ = Alignment::CENTER_ORIGIN;

    updateBBox();
}

void milk::BoxCollider::updateBBox() {
    Vector2d actorPosition = actor_.position();

    // Update the old bounding box before invalidating the current one.
    oldRect_ = rect_;

    switch (origin_) {
        case Alignment::TOP_LEFT:
            rect_.x = (int)(actorPosition.x + offset_.x);
            rect_.y = (int)(actorPosition.y + offset_.y);
            break;
        case Alignment::CENTER_ORIGIN:
            rect_.x = (int)(actorPosition.x - (rect_.w / 2) + offset_.x);
            rect_.y = (int)(actorPosition.y - (rect_.h / 2) + offset_.y);
            break;
    }

    if (grid_ != nullptr)
        grid_->move(this);
}

SDL_Rect milk::BoxCollider::rect() const {
    return rect_;
}

void milk::BoxCollider::width(int width) {
    rect_.w = width;
}

void milk::BoxCollider::height(int height) {
    rect_.h = height;
}

void milk::BoxCollider::offset(int x, int y) {
    offset_.x = x;
    offset_.y = y;
}

bool milk::BoxCollider::overlaps(SDL_Rect otherRect) const {
    return SDL_HasIntersection(&rect_, &otherRect);
}

bool milk::BoxCollider::overlaps(SDL_Rect otherRect, SDL_Rect* result) const {
    return SDL_IntersectRect(&rect_, &otherRect, result);
}

int milk::BoxCollider::top() {
    return rect_.y;
}

int milk::BoxCollider::bottom() {
    return rect_.y + rect_.h;
}

int milk::BoxCollider::left() {
    return rect_.x;
}

int milk::BoxCollider::right() {
    return rect_.x + rect_.w;
}
