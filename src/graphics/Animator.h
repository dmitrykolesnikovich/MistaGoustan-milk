#ifndef MILK_ANIMATOR_H
#define MILK_ANIMATOR_H

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "scene/ActorComponent.h"
#include "utilities/Timer.h"

namespace milk
{
    class Sprite;

    struct Animation
    {
        explicit Animation(std::string nm)
                : name(std::move(nm))
        {
        }

        // Name of animation
        const std::string name;

        // Animation frames
        std::vector<int> frames;
    };

    class Animator : public ActorComponent
    {
    public:
        static const ComponentType type;

        Animator(Actor& actor,
                 int rows,
                 int columns,
                 float timeBetweenFrames = 0.1f);

        ~Animator() override = default;

        // Initialize the animator.
        void init();

        // Toggle animation paused.
        void togglePaused();

        // Add an animation.
        void addAnimation(const Animation& animation);

        // Sets the current animation.
        void setAnimation(const std::string& name);

        // Updates the animators state.
        void update();

    private:
        Sprite* sprite_;

        Timer timer_;
        int currentFrame_;
        float timeBetweenFrames_;

        int rows_;
        int columns_;
        int frameWidth_;
        int frameHeight_;

        std::unordered_map<std::string, std::unique_ptr<Animation>> animations_;
        Animation* currentAnimation_;

        void updateSourceRect();
    };
}

#endif
