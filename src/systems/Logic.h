#ifndef _LOGIC_SYSTEM_
#define _LOGIC_SYSTEM_

#include <unordered_map>

#include "../externals/sol.hpp"

class Actor;
class Script;

class Logic
{
public:
	Logic(sol::state& luaState);
	~Logic() = default;

	void onActorAdded(Actor& actor);
	void onActorDestroyed(Actor& actor);

	void update();

private:
	sol::state& luaState_;

	std::unordered_map<int, Script*> scriptByActorId_;
};

#endif
