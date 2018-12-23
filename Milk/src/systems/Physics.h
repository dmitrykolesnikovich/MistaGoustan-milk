#ifndef _PHYSICS_SYSTEM_
#define _PHYSICS_SYSTEM_

#include <unordered_map>

class Actor;
class Velocity;

class Physics 
{
public:
	Physics() = default;
	~Physics() = default;

	void onActorAdded(Actor& actor);
	void onActorDestroyed(Actor& actor);

	void update();

private:
	std::unordered_map<int, Velocity*> velocityByActorId_;
};

#endif
