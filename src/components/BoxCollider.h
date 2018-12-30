#ifndef _BOX_COLLIDER_
#define _BOX_COLLIDER_

#include "SDL.h"

#include "../core/ActorComponent.h"

#include "../math/Vector2d.h"

#include "../utilities/Alignment.h"

class SpatialPartitionGrid;

class BoxCollider : public ActorComponent
{
public:
	static const ComponentType type;

	friend class SpatialPartitionGrid;

	BoxCollider(Actor& actor);
	~BoxCollider();

	void init(SpatialPartitionGrid* grid);

	// Center the colliders origin.
	void center();

	// Update the bounding box. This is called every time the actors position changes.
	void updateBBox();
	
	// Returns the colliders rect.
	SDL_Rect rect() const;

	// Sets the width of the collider.
	void width(int width);

	// Sets the height of the collider.
	void height(int height);

	// Offset the collider.
	void offset(int x, int y);

	// Returns true if collider is overlapping another rect.
	bool overlaps(SDL_Rect otherRect) const;

	// Returns true if collider if overlapping another rect and outputs the depth rect.
	bool overlaps(SDL_Rect otherRect, SDL_Rect* result) const;

private:
	Alignment alignment_;

	SDL_Rect rect_;
	SDL_Rect oldRect_;

	Vector2d offset_;

	SpatialPartitionGrid* grid_;

	BoxCollider* prev_;
	BoxCollider* next_;
};

#endif
