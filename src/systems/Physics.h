#ifndef _PHYSICS_SYSTEM_
#define _PHYSICS_SYSTEM_

#include <memory>
#include <unordered_map>

class Actor;
class BoxCollider;
class Velocity;

struct DynamicNode 
{
	DynamicNode(Actor& actor)
		: actor(actor)
	{
		previous = nullptr;
		next = nullptr;
	}

	Actor& actor;

	DynamicNode* previous;
	DynamicNode* next;
};

struct CollisionPair 
{
	BoxCollider* coll1;
	BoxCollider* coll2;
};

class Physics 
{
public:
	Physics() = default;
	~Physics() = default;

	void onActorAdded(Actor& actor);
	void onActorDestroyed(Actor& actor);

	void update();

private:
	DynamicNode* first_;
	DynamicNode* last_;

	std::unordered_map<int, Velocity*> movableActors_;
	std::unordered_map<int, BoxCollider*> collidableActors_;
	std::unordered_map<int, std::unique_ptr<DynamicNode>> dynamicActors_;
};

#endif
