#ifndef MILK_ANIMATOR_H
#define MILK_ANIMATOR_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "core/ActorComponent.h"
#include "utilities/Timer.h"

namespace milk {
    class Sprite;

    struct Animation {
        Animation(const std::string& n, std::initializer_list<int> f) {
            name = n;
            frames = new int[f.size()];

            int i = 0;
            for (auto it : f) {
                frames[i] = it;
                ++i;
            }

            size = (int)f.size();
        }

        Animation(const std::string& n, std::vector<int> f) {
            name = n;
            frames = new int[f.size()];

            int i = 0;
            for (auto it : f) {
                frames[i] = it;
                ++i;
            }

            size = f.size();
        }

        ~Animation() {
            delete[] frames;
        }

        std::string name;
        int* frames;
        int size;
    };

    class Animator : public ActorComponent {
    public:
        static const ComponentType type;

        explicit Animator(Actor& actor);

        ~Animator() override = default;

        // Initialize the animator.
        void init();

        // Sets the amount of rows in the source sprite sheet.
        void rows(int rows);

        // Sets the amount of columns in the source sprite sheet.
        void columns(int columns);

        // Toggle animation paused.
        void togglePaused();

        // Add an animation.
        void addAnimation(const std::string& name, std::initializer_list<int> frames);

        // Add an animation.
        void addAnimation(const std::string& name, std::vector<int> frames);

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

        bool paused_;

        Animation* currentAnimation_;
        std::unordered_map<std::string, std::unique_ptr<Animation>> animations_;
    };
}

#endif
