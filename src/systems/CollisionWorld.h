#ifndef _COLLISION_WORLD_
#define _COLLISION_WORLD_

class BoxCollider;

class CollisionWorld
{
public:
	virtual void add(BoxCollider* collider) = 0;
	virtual void move(BoxCollider* collider) = 0;
};

#endif
