#ifndef _PHYSICS_SYSTEM_
#define _PHYSICS_SYSTEM_

#include <memory>
#include <unordered_map>

#include "SpatialPartitionGrid.h"

class Actor;
class BoxCollider;
class EventQueue;
class Velocity;

class Physics 
{
public:
	Physics(EventQueue& eventQueue);
	~Physics() = default;

	void onActorAdded(Actor& actor);
	void onActorDestroyed(Actor& actor);

	void update();

private:
	EventQueue& eventQueue_;

	std::unordered_map<int, Velocity*> velocityByActorId_;
	std::unique_ptr<SpatialPartitionGrid> partitionGrid_;
};

#endif
