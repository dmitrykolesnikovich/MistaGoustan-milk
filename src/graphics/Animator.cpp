#include "Animator.h"

#include <memory>

#include "SDL.h"

#include "Sprite.h"
#include "Texture.h"

#include "scene/Actor.h"

const milk::ComponentType milk::Animator::type = ANIMATOR;

milk::Animator::Animator(Actor& actor, int rows, int columns, float timeBetweenFrames)
        : ActorComponent::ActorComponent(actor), rows_(rows), columns_(columns), timeBetweenFrames_(timeBetweenFrames),
          frameWidth_(0), frameHeight_(0), currentAnimation_(nullptr) {
}

void milk::Animator::init() {
    sprite_ = actor_.getComponent<Sprite>();

    // TODO: log message.
    if (sprite_ == nullptr)
        return;

    auto texture = sprite_->texture();

    frameWidth_ = texture->width() / columns_;
    frameHeight_ = texture->height() / rows_;
}

void milk::Animator::togglePaused() {
    if (timer_.isPaused())
        timer_.unpause();
    else
        timer_.pause();
}

void milk::Animator::addAnimation(const Animation& animation) {
    animations_.insert(std::make_pair(animation.name, std::make_unique<Animation>(animation)));
}

void milk::Animator::setAnimation(const std::string& name) {
    if (currentAnimation_ != nullptr && currentAnimation_->name == name)
        return;

    currentAnimation_ = animations_.at(name).get();
    currentFrame_ = 0;

    timer_.start();

    updateSourceRect();
}

void milk::Animator::update() {
    if (currentAnimation_ != nullptr && !timer_.isPaused()) {
        auto frameTime = timer_.getTicks() / 1000.0f;

        if (frameTime > timeBetweenFrames_) {
            timer_.start();

            currentFrame_++;

            if (currentFrame_ > currentAnimation_->frames.size() - 1)
                currentFrame_ = 0;

            updateSourceRect();
        }
    }
}

void milk::Animator::updateSourceRect() {
    int row = (int)((float)currentAnimation_->frames[currentFrame_] / columns_);
    int column = currentAnimation_->frames[currentFrame_] % columns_;

    sprite_->sourceRect(column * frameWidth_, row * frameHeight_, frameWidth_, frameHeight_);
}
