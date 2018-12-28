#include "Logic.h"

#include "../core/Actor.h"
#include "../components/Script.h"

Logic::Logic(sol::state& luaState)
	: luaState_(luaState)
{
}

void Logic::onActorAdded(Actor& actor)
{
	Script* script = actor.getComponent<Script>();

	if (script == nullptr)
		return;

	scriptByActorId_.insert(std::make_pair(actor.id(), script));

	script->load(luaState_);

	script->begin();
}

void Logic::onActorDestroyed(Actor& actor)
{
	auto found = scriptByActorId_.find(actor.id());

	if (found == scriptByActorId_.end())
		return;

	Script* Script = found->second;

	if (Script == nullptr)
		return;

	Script->end();

	scriptByActorId_.erase(actor.id());
}

void Logic::update()
{
	for (auto& it : scriptByActorId_) 
	{
		it.second->update();
	}
}
