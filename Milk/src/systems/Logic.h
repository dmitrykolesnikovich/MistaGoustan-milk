#ifndef _LOGIC_SYSTEM_
#define _LOGIC_SYSTEM_

#include <unordered_map>

class Actor;
class Behavior;

class Logic
{
public:
	Logic() = default;
	~Logic() = default;

	void onActorAdded(Actor& actor);
	void onActorDestroyed(Actor& actor);

	void update();

private:
	std::unordered_map<int, Behavior*> behaviorByActorId_;
};

#endif
