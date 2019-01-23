#ifndef _PHYSICS_SYSTEM_
#define _PHYSICS_SYSTEM_

#include <memory>
#include <unordered_map>

class Actor;
class BoxCollider;
class EventQueue;
class GameEvent;
class SpatialPartitionGrid;
class Velocity;

class Physics 
{
public:
	explicit Physics(EventQueue& eventQueue);
	~Physics();

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
