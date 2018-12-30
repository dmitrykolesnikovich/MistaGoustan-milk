#include "SpatialPartitionGrid.h"

#include <iostream>

#include "../core/Actor.h"
#include "../components/BoxCollider.h"

SpatialPartitionGrid::SpatialPartitionGrid()
{
	for (int x = 0; x < NUM_CELLS; x++)
	{
		for (int y = 0; y < NUM_CELLS; y++)
		{
			cells_[x][y] = nullptr;
		}
	}
}

void SpatialPartitionGrid::add(BoxCollider* collider)
{
	// Determine which grid cell it's in.
	int cellX = (int)(collider->rect().x / SpatialPartitionGrid::CELL_SIZE);
	int cellY = (int)(collider->rect().y/ SpatialPartitionGrid::CELL_SIZE);

	// Add to the front of list for the cell it's in.
	collider->prev_ = nullptr;
	collider->next_ = cells_[cellX][cellY];
	cells_[cellX][cellY] = collider;

	if (collider->next_ != nullptr)
	{
		collider->next_->prev_ = collider;
	}
}

void SpatialPartitionGrid::move(BoxCollider* collider)
{
	// See which cell it was in.
	int oldCellX = (int)(collider->oldRect_.x / SpatialPartitionGrid::CELL_SIZE);
	int oldCellY = (int)(collider->oldRect_.y / SpatialPartitionGrid::CELL_SIZE);

	// See which cell it's moving to.
	int cellX = (int)(collider->rect_.x / SpatialPartitionGrid::CELL_SIZE);
	int cellY = (int)(collider->rect_.y / SpatialPartitionGrid::CELL_SIZE);

	// If it didn't change cells, we're done.
	if (oldCellX == cellX && oldCellY == cellY)
		return;

	// Unlink it from the list of its old cell.
	if (collider->prev_ != nullptr)
	{
		collider->prev_->next_ = collider->next_;
	}

	if (collider->next_ != nullptr)
	{
		collider->next_->prev_ = collider->prev_;
	}

	// If it's the head of a list, remove it.
	if (cells_[oldCellX][oldCellY] == collider)
	{
		cells_[oldCellX][oldCellY] = collider->next_;
	}

	// Add it back to the grid at its new cell.
	add(collider);
}

std::vector<Collision> SpatialPartitionGrid::getCollisions(BoxCollider* collider)
{
	std::vector<Collision> collisions;

	int x = (int)(collider->rect().x / SpatialPartitionGrid::CELL_SIZE);
	int y = (int)(collider->rect().y / SpatialPartitionGrid::CELL_SIZE);

	// Get collisions for current cell.
	getCollisionForCell(collider, cells_[x][y], &collisions);

	// Get collisions for surrounding cells
	// Upper left cell
	if (x > 0 && y > 0)
		getCollisionForCell(collider, cells_[x - 1][y - 1], &collisions);

	// Left cell
	if (x > 0) 
		getCollisionForCell(collider, cells_[x - 1][y], &collisions);

	// Upper cell
	if (y > 0)
		getCollisionForCell(collider, cells_[x][y - 1], &collisions);

	// Bottom left cell
	if (x > 0 && y < NUM_CELLS - 1)	
		getCollisionForCell(collider, cells_[x - 1][y + 1], &collisions);

	// Upper right cell
	if (x < NUM_CELLS -1 && y > 0)
		getCollisionForCell(collider, cells_[x + 1][y - 1], &collisions);

	// Right cell
	if (x < NUM_CELLS -1)
		getCollisionForCell(collider, cells_[x + 1][y], &collisions);

	// Bottom cell
	if (y < NUM_CELLS -1)
		getCollisionForCell(collider, cells_[x][y + 1], &collisions);

	// Bottom right cell
	if (x < NUM_CELLS -1 && y < NUM_CELLS - 1)
		getCollisionForCell(collider, cells_[x + 1][y + 1], &collisions);

	return collisions;
}

void SpatialPartitionGrid::getCollisionForCell(BoxCollider* collider, BoxCollider* cell, std::vector<Collision>* collisions)
{
	while (cell != nullptr)
	{
		if (collider != cell)
		{
			if (collider->overlaps(cell->rect()))
			{
				// TODO get direction of collision
				collisions->emplace_back(cell, CollisionDirection::DOWN);
			}
		}

		cell = cell->next_;
	}
}
