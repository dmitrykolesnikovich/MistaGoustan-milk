#include "Logic.h"

#include "../components/Script.h"

#include "../core/Actor.h"

#include "../systems/ActorEventList.h"

Logic::Logic(sol::state& luaState)
	: luaState_(luaState)
{
}

void Logic::handleEvent(ActorEvent& gameEvent)
{
	switch (gameEvent.type())
	{
	case ActorEventType::ACTOR_SPAWNED: 
	{
		auto& spawnedEvent = dynamic_cast<ActorSpawnedEvent&>(gameEvent);
		onActorSpawned(spawnedEvent.actor());
	}
		break;
	case ActorEventType::ACTOR_DETROYED: 
	{
		auto& destroyedEvent = dynamic_cast<ActorDestroyedEvent&>(gameEvent);
		onActorDestroyed(destroyedEvent.actor());
	}
		break;
	case ActorEventType::ACTOR_COLLISION: 
	{
		auto& collisionEvent = dynamic_cast<ActorCollisionEvent&>(gameEvent);
		onActorCollision(collisionEvent);
	}
		break;
	}
}

void Logic::update()
{
	for (auto& it : scriptByActorId_)	
		it.second->update();	
}

void Logic::onActorSpawned(Actor& actor)
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

	Script* script = found->second;

	if (script == nullptr)
		return;

	script->end();

	scriptByActorId_.erase(actor.id());
}

void Logic::onActorCollision(ActorCollisionEvent& collisionEvent)
{
	auto script = scriptByActorId_.find(collisionEvent.actor().id());

	if (script != scriptByActorId_.end())
		script->second->onCollision(collisionEvent);
}
