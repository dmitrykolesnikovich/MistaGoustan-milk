#ifndef _LUA_HANDLE_ACTOR_
#define _LUA_HANDLE_ACTOR_

#include "../externals/sol.hpp"

class Actor;

class LuaHandle_Actor
{
public:
	LuaHandle_Actor(Actor& actor);
	LuaHandle_Actor() = default;

	// Move the actor.
	void move(float x, float y);

private:
	Actor& actor_;
};

#endif
