// http://gameprogrammingpatterns.com/spatial-partition.html

#ifndef _SPATIAL_PARTITION_GRID_
#define _SPATIAL_PARTITION_GRID_

#include <vector>

#include "SDL.h"

class BoxCollider;

enum class CollisionSide 
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

struct CollisionEvent
{
	CollisionEvent(BoxCollider* o, CollisionSide dir, SDL_Rect depth) 
	{
		other = o;
		direction = dir;
		depthRect = depth;
	}

	// The other collider.
	BoxCollider* other;

	// The direction of collision from subject to other.
	CollisionSide direction;

	// The intersection depth between the two colliders.
	SDL_Rect depthRect;
};

// The spatial partition grid divides the scene into cells.
// Each cell contains collidable actors.
// When checking for collisions with a given collider, it only queries the current and neighboring cells.
class SpatialPartitionGrid
{
public:
	SpatialPartitionGrid();

	// Adds a collider to the collision grid.
	void add(BoxCollider* collider);

	// Removes a collider from the collision grid.
	void remove(BoxCollider* collider);

	// Removes a collider from the collision grid.
	void move(BoxCollider* collider);

	// Get all colliders than intersect with a given collider.
	std::vector<CollisionEvent> getCollisions(BoxCollider* collider);

	// TODO make these data driven
	// TODO NUM_HORIZONTAL_CELLS & NUM_VERTICAL_CELLS
	static const int NUM_CELLS = 4;
	static const int CELL_SIZE = 160;
private:
	BoxCollider* cells_[NUM_CELLS][NUM_CELLS];

	void getCollisionForCell(BoxCollider* collider, BoxCollider* cell, std::vector<CollisionEvent>* collisions);
};

#endif
