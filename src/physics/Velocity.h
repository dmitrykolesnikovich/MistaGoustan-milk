#ifndef MILK_VELOCITY_H
#define MILK_VELOCITY_H

#include "scene/ActorComponent.h"

#include "math/Vector2d.h"

namespace milk
{
    // All objects that move should own a velocity component.
    // In regards to movement, directly setting an objects position is ill advised as the collision system operates on Velocity.
    class Velocity : public ActorComponent
    {
    public:
        static const ComponentType type;

        explicit Velocity(Actor& actor);

        ~Velocity() override = default;

        // Sets the velocity.
        void value(float x, float y);

        // Sets the velocity.
        void value(Vector2d velocity);

        // Gets the velocity.
        Vector2d value() const;

    private:
        Vector2d value_;
    };
}

#endif
