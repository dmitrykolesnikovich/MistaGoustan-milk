#include "Logic.h"

#include "../core/Actor.h"
#include "../components/Behavior.h"

void Logic::onActorAdded(Actor& actor)
{
	Behavior* behavior = actor.getComponent<Behavior>();

	if (behavior == nullptr)
		return;

	behaviorByActorId_.insert(std::make_pair(actor.getId(), behavior));

	behavior->begin();
}

void Logic::onActorDestroyed(Actor& actor)
{
	auto found = behaviorByActorId_.find(actor.getId());

	if (found == behaviorByActorId_.end())
		return;

	Behavior* behavior = found->second;

	if (behavior == nullptr)
		return;

	behavior->end();

	behaviorByActorId_.erase(actor.getId());
}

void Logic::update()
{
	for (auto& it : behaviorByActorId_) 
	{
		it.second->update();
	}
}
