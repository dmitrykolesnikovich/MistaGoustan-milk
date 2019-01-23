#ifndef _LOGIC_SYSTEM_
#define _LOGIC_SYSTEM_

#include <unordered_map>

#include "externals/sol.hpp"

class Actor;
class ActorCollisionEvent;
class GameEvent;
class Script;

class Logic
{
public:
	explicit Logic(sol::state& luaState);
	~Logic() = default;

	void handleEvent(GameEvent& gameEvent);

	void update();

private:
	sol::state& luaState_;

	std::unordered_map<int, Script*> scriptByActorId_;

	void onActorSpawned(Actor& actor);
	void onActorDestroyed(Actor& actor);
	void onActorCollision(ActorCollisionEvent& collisionEvent);
};

#endif
