#ifndef _LUA_HANDLE_ACTOR_
#define _LUA_HANDLE_ACTOR_

#include <string>

#include "../externals/sol.hpp"

class Actor;

class LuaHandle_Actor
{
public:
	LuaHandle_Actor(Actor& actor);
	LuaHandle_Actor() = default;

	void setAsCameraTarget();

	// Move the actor.
	void move(float x, float y);

	// Set the actors animation.
	void setAnimation(const std::string& name);

	// Flips the actor horizontally.
	void flipX();

	// Flips the actor vertically.
	void flipY();

private:
	Actor& actor_;
};

#endif
