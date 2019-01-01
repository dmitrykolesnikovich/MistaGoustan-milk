#ifndef _EVENT_QUEUE_
#define _EVENT_QUEUE_

#include <memory>
#include <queue>
#include <vector>

#include "../components/BoxCollider.h"

enum class ActorEventType 
{
	// Prioritized by greatest value.
	ACTOR_COLLISION,
	ACTOR_TRIGGER,
	ACTOR_SPAWNED,
	ACTOR_DETROYED
};

class ActorEvent 
{
public:
	ActorEvent(ActorEventType type, Actor& actor) 
		: type_(type)
		, actor_(actor)
	{
	}

	virtual ~ActorEvent() = default;

	ActorEventType type() const { return type_; }
	Actor& actor() const { return actor_; }

private:
	ActorEventType type_;
	Actor& actor_;
};

struct ActorEventComparison 
{
	bool operator()(const std::shared_ptr<ActorEvent>& first, const std::shared_ptr<ActorEvent>& second) 
	{
		return first->type() < second->type();
	}
};

class ActorEventQueue
{
public:
	void pushEvent(ActorEvent* gameEvent);

	std::shared_ptr<ActorEvent> popEvent();

	bool empty();

private:
	std::priority_queue<std::shared_ptr<ActorEvent>, std::vector<std::shared_ptr<ActorEvent>>, ActorEventComparison> events_;
};

#endif
