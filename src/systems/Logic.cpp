#include "Logic.h"

#include "../components/Script.h"
#include "../core/Actor.h"



#include "EventQueue.h"

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

void Logic::handleEvent(GameEvent& gameEvent)
{
	switch (gameEvent.type())
	{
	case GameEventType::ACTOR_COLLISION:
		auto& e = dynamic_cast<ActorCollisionEvent&>(gameEvent);
		auto& script = scriptByActorId_.find(e.actorId());

		if (script != scriptByActorId_.end())
			script->second->onCollision(e);
		break;
	}
}

void Logic::update()
{
	for (auto& it : scriptByActorId_)
	{
		it.second->update();
	}
}
