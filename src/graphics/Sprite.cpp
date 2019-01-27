#include "Sprite.h"

#include "graphics/Texture.h"

#include "math/Vector2d.h"

#include "scene/Actor.h"

#include "utilities/ResourceManager.h"

const milk::ComponentType milk::Sprite::type = SPRITE;

milk::Sprite::Sprite(milk::Actor& actor, const std::string& textureName)
        : ActorComponent::ActorComponent(actor), textureName_(textureName), alignment_(Alignment::TOP_LEFT),
          flip_(SDL_FLIP_NONE) {

    sourceRect_ = {0, 0, 0, 0};
}

void milk::Sprite::load(AssetLoader<Texture>& textureLoader) {
    texture_ = textureLoader.load(textureName_);

    // If the source rect was never explictly set, lets default it to texture rect.
    if (SDL_RectEmpty(&sourceRect_)) {
        sourceRect_.x = 0;
        sourceRect_.y = 0;
        sourceRect_.w = texture_->width();
        sourceRect_.h = texture_->height();
    }
}

std::shared_ptr<milk::Texture> milk::Sprite::texture() const {
    return texture_;
}

void milk::Sprite::center() {
    alignment_ = Alignment::CENTER_ORIGIN;
}

void milk::Sprite::sourceRect(int x, int y, int width, int height) {
    sourceRect_.x = x;
    sourceRect_.y = y;
    sourceRect_.w = width;
    sourceRect_.h = height;
}

SDL_Rect milk::Sprite::sourceRect() const {
    return sourceRect_;
}

SDL_Rect milk::Sprite::destinationRect() const {
    Vector2d actorPosition = actor_.position();

    SDL_Rect destinationRect;
    destinationRect.w = sourceRect_.w;
    destinationRect.h = sourceRect_.h;

    switch (alignment_) {
        case Alignment::TOP_LEFT:
            destinationRect.x = (int)std::floor(actorPosition.x);
            destinationRect.y = (int)std::floor(actorPosition.y);
            break;
        case Alignment::CENTER_ORIGIN:
            destinationRect.x = (int)std::floor(actorPosition.x) - (sourceRect_.w / 2);
            destinationRect.y = (int)std::floor(actorPosition.y) - (sourceRect_.h / 2);
            break;
    }

    return destinationRect;
}

void milk::Sprite::flipX() {
    if (flippedX())
        flip_ &= ~SDL_FLIP_HORIZONTAL;
    else
        flip_ |= SDL_FLIP_HORIZONTAL;
}

bool milk::Sprite::flippedX() {
    return (flip_ & SDL_FLIP_HORIZONTAL) == SDL_FLIP_HORIZONTAL;
}

void milk::Sprite::flipY() {
    if (flippedY())
        flip_ &= ~SDL_FLIP_VERTICAL;
    else
        flip_ |= SDL_FLIP_VERTICAL;
}

bool milk::Sprite::flippedY() {
    return (flip_ & SDL_FLIP_VERTICAL) == SDL_FLIP_VERTICAL;
}

SDL_RendererFlip milk::Sprite::rendererFlip() const {
    return (SDL_RendererFlip)flip_;
}
