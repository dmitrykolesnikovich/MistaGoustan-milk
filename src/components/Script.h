#ifndef _Script_
#define _Script_

#include <string>

#include "../core/ActorComponent.h"
#include "../externals/sol.hpp"

class LuaHandle_Actor;

class Script : public ActorComponent
{
public:
	static const ComponentType type;

	Script(Actor& actor);
	~Script() = default;

	// Set the name of the script to load.
	void script(const std::string& scriptName);

	// Load the script.
	void load(sol::state& luaState);

	// Called once the actor has been spawned into the scene.
	virtual void begin();

	// Called once per frame.
	virtual void update();

	// Called once the actor has been destroyed.
	virtual void end();

private:
	std::string scriptName_;
	sol::table luaScript_;
};

#endif
