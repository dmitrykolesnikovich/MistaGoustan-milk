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

	void script(const std::string& scriptName);
	void load(sol::state& luaState);

	virtual void begin();
	virtual void update();
	virtual void end();

private:
	std::string scriptName_;
	sol::table luaScript_;
};

#endif
