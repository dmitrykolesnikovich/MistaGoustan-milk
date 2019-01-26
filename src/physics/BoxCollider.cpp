#include "BoxCollider.h"

#include "core/Actor.h"
#include "SpatialPartitionGrid.h"

const ComponentType BoxCollider::type = BOX_COLLIDER;

BoxCollider::BoxCollider(Actor& actor)
        : ActorComponent::ActorComponent(actor), origin_(Alignment::TOP_LEFT), offset_(0, 0), grid_(nullptr),
          next_(nullptr), prev_(nullptr) {

    updateBBox();
}

void BoxCollider::init(SpatialPartitionGrid* grid) {
    grid_ = grid;

    updateBBox();
}

void BoxCollider::center() {
    origin_ = Alignment::CENTER_ORIGIN;

    updateBBox();
}

void BoxCollider::updateBBox() {
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

SDL_Rect BoxCollider::rect() const {
    return rect_;
}

void BoxCollider::width(int width) {
    rect_.w = width;
}

void BoxCollider::height(int height) {
    rect_.h = height;
}

void BoxCollider::offset(int x, int y) {
    offset_.x = x;
    offset_.y = y;
}

bool BoxCollider::overlaps(SDL_Rect otherRect) const {
    return SDL_HasIntersection(&rect_, &otherRect);
}

bool BoxCollider::overlaps(SDL_Rect otherRect, SDL_Rect* result) const {
    return SDL_IntersectRect(&rect_, &otherRect, result);
}

int BoxCollider::top() {
    return rect_.y;
}

int BoxCollider::bottom() {
    return rect_.y + rect_.h;
}

int BoxCollider::left() {
    return rect_.x;
}

int BoxCollider::right() {
    return rect_.x + rect_.w;
}
