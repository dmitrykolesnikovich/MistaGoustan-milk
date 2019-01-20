#ifndef _PHYSICS_SYSTEM_
#define _PHYSICS_SYSTEM_

#include <memory>
#include <unordered_map>

#include "SpatialPartitionGrid.h"

class Actor;
class ActorEvent;
class ActorEventQueue;
class BoxCollider;
class Velocity;

class Physics 
{
public:
	explicit Physics(ActorEventQueue& eventQueue);
	~Physics() = default;

	void handleEvent(ActorEvent& gameEvent);

	void update();

private:
	ActorEventQueue& eventQueue_;

	std::unordered_map<int, Velocity*> velocityByActorId_;
	std::unique_ptr<SpatialPartitionGrid> partitionGrid_;

	void onActorSpawned(Actor& actor);
	void onActorDestroyed(Actor& actor);
};

#endif
