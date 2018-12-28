#ifndef _BEHAVIOR_
#define _BEHAVIOR_

#include <string>

#include "../core/ActorComponent.h"
#include "../externals/sol.hpp"

class Behavior : public ActorComponent
{
public:
	static const ComponentType type;

	Behavior(Actor& actor);
	~Behavior();

	void script(const std::string& scriptName);
	void load(sol::state& luaState);

	virtual void begin();
	virtual void update();
	virtual void end();

private:
	std::string scriptName_;
	sol::table luaBehavior_;
};

#endif
