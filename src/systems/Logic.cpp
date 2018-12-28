#include "Logic.h"

#include "../core/Actor.h"
#include "../components/Behavior.h"

Logic::Logic(sol::state& luaState)
	: luaState_(luaState)
{
}

void Logic::onActorAdded(Actor& actor)
{
	Behavior* behavior = actor.getComponent<Behavior>();

	if (behavior == nullptr)
		return;

	behaviorByActorId_.insert(std::make_pair(actor.id(), behavior));

	behavior->load(luaState_);

	behavior->begin();
}

void Logic::onActorDestroyed(Actor& actor)
{
	auto found = behaviorByActorId_.find(actor.id());

	if (found == behaviorByActorId_.end())
		return;

	Behavior* behavior = found->second;

	if (behavior == nullptr)
		return;

	behavior->end();

	behaviorByActorId_.erase(actor.id());
}

void Logic::update()
{
	for (auto& it : behaviorByActorId_) 
	{
		it.second->update();
	}
}
