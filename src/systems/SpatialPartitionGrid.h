// http://gameprogrammingpatterns.com/spatial-partition.html

#ifndef _SPATIAL_PARTITION_GRID_
#define _SPATIAL_PARTITION_GRID_

#include <vector>

#include "SDL.h"

class BoxCollider;

enum class CollisionDirection 
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

struct Collision
{
	Collision(BoxCollider* o, CollisionDirection dir, SDL_Rect depth) 
	{
		other = o;
		direction = dir;
		depthRect = depth;
	}

	BoxCollider* other;
	CollisionDirection direction;
	SDL_Rect depthRect;
};

class SpatialPartitionGrid
{
public:
	SpatialPartitionGrid();

	void add(BoxCollider* collider);
	void move(BoxCollider* collider);
	std::vector<Collision> getCollisions(BoxCollider* collider);

	static const int NUM_CELLS = 2;
	static const int CELL_SIZE = 320;
private:
	BoxCollider* cells_[NUM_CELLS][NUM_CELLS];

	void getCollisionForCell(BoxCollider* collider, BoxCollider* cell, std::vector<Collision>* collisions);
};

#endif
