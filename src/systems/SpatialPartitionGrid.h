#ifndef _SPATIAL_PARTITION_GRID_
#define _SPATIAL_PARTITION_GRID_

#include <vector>

#include "CollisionWorld.h"

enum class CollisionDirection 
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct Collision
{
	Collision(BoxCollider* o, CollisionDirection dir) 
	{
		other = o;
	}

	BoxCollider* other;
	CollisionDirection direction;
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
