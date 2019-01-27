#ifndef MILK_CAMERA_H
#define MILK_CAMERA_H

#include "SDL.h"

#include "math/Vector2d.h"

namespace milk {
    class Actor;

    class Scene;

    class Camera {
    public:
        Camera(Scene& scene, unsigned int width, unsigned int height);

        ~Camera() = default;

        // Set the cameras position.
        void position(float x, float y);

        // Get the cameras position.
        Vector2d position() const;

        // Set the cameras target to follow.
        void setTarget(Actor* actor);

        // Update the camera.
        void update();

    private:
        Scene& scene_;

        Actor* target_;

        SDL_Rect camRect_;

        void followTarget();

        void clampCameraToSceneBounds();
    };
}

#endif
