#ifndef _ACTOR_EVENT_LIST_
#define _ACTOR_EVENT_LIST_

#include "ActorEventQueue.h"

class ActorSpawnedEvent : public ActorEvent
{
public:
	explicit ActorSpawnedEvent(Actor& actor)
		: ActorEvent::ActorEvent(ActorEventType::ACTOR_SPAWNED, actor)
	{
	}
};

class ActorDestroyedEvent : public ActorEvent
{
public:
	explicit ActorDestroyedEvent(Actor& actor)
		: ActorEvent::ActorEvent(ActorEventType::ACTOR_DETROYED, actor)
	{
	}
};

class ActorCollisionEvent : public ActorEvent
{
public:
	ActorCollisionEvent(Actor& actor, BoxCollider& collider)
		: ActorEvent::ActorEvent(ActorEventType::ACTOR_COLLISION, actor)
		, otherCollider_(collider)
	{
	}

	BoxCollider& collider() { return otherCollider_; }

private:
	BoxCollider& otherCollider_;
};

#endif
