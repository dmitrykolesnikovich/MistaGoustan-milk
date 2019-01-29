#ifndef MILK_BOX_COLLIDER_H
#define MILK_BOX_COLLIDER_H

#include "SDL.h"

#include "scene/ActorComponent.h"

#include "math/Vector2d.h"

#include "utilities/Alignment.h"

namespace milk
{
    class SpatialPartitionGrid;

// Actors with a box collider will be static collidable objects.
// Actors with a box collider and velocity will be dynamic collidable objects.
    class BoxCollider : public ActorComponent
    {
    public:
        static const ComponentType type;

        friend class SpatialPartitionGrid;

        explicit BoxCollider(Actor& actor);

        ~BoxCollider() override = default;

        // Initializes the collider so it can become one with the collision grid.
        void init(SpatialPartitionGrid* grid);

        // Centers the collider's origin.
        void center();

        // Updates the bounding box. If the actor's position is changed, this method must be called in order to update the collider's bounding box.
        void updateBBox();

        // Returns the collider's bounding box.
        SDL_Rect rect() const;

        // Sets the width of the collider.
        void width(int width);

        // Sets the height of the collider.
        void height(int height);

        // Offsets the collider.
        void offset(int x, int y);

        // Returns true if collider's bounding box is overlapping another collider's bounding box.
        bool overlaps(SDL_Rect otherRect) const;

        // Returns true if collider's bounding box is overlapping another collider's bounding box, and outputs the depth rect.
        bool overlaps(SDL_Rect otherRect, SDL_Rect* result) const;

        // Top of collider.
        int top();

        // Bottom of collider.
        int bottom();

        // Left of collider.
        int left();

        // Right of collider;
        int right();

    private:
        Alignment origin_;

        SDL_Rect rect_;
        SDL_Rect oldRect_;

        Vector2d offset_;

        SpatialPartitionGrid* grid_;

        BoxCollider* prev_;
        BoxCollider* next_;
    };
}

#endif
