#ifndef _PHYSICS_SYSTEM_
#define _PHYSICS_SYSTEM_

#include <memory>
#include <unordered_map>

#include "SpatialPartitionGrid.h"

class Actor;
class GameEvent;
class EventQueue;
class BoxCollider;
class Velocity;

class Physics 
{
public:
	explicit Physics(EventQueue& eventQueue);
	~Physics() = default;

	void handleEvent(GameEvent& gameEvent);

	void update();

private:
	EventQueue& eventQueue_;

	std::unordered_map<int, Velocity*> velocityByActorId_;
	std::unique_ptr<SpatialPartitionGrid> partitionGrid_;

	void onActorSpawned(Actor& actor);
	void onActorDestroyed(Actor& actor);
};

#endif
