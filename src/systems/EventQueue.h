#ifndef _EVENT_QUEUE_
#define _EVENT_QUEUE_

#include <memory>
#include <queue>

#include "../components/BoxCollider.h"

enum class GameEventType 
{
	ACTOR_SPAWNED,
	ACTOR_DETROYED,
	ACTOR_COLLISION,
	ACTOR_TRIGGER
};

class GameEvent 
{
public:
	GameEvent(GameEventType type) 
		: type_(type)
	{
	}

	virtual ~GameEvent() = default;

	GameEventType type() const { return type_; }

private:
	GameEventType type_;
};

/////////////////////////////
class ActorCollisionEvent : public GameEvent
{
public:
	ActorCollisionEvent(unsigned int actorId, BoxCollider& collider) 
		: GameEvent::GameEvent(GameEventType::ACTOR_COLLISION)
		, actorId_(actorId)
		, otherCollider_(collider)
	{
	}

	unsigned int actorId() { return actorId_; }
	BoxCollider& collider() { return otherCollider_; }

private:
	unsigned int actorId_;
	BoxCollider& otherCollider_;
};
/////////////////////////////

class EventQueue
{
public:
	void pushEvent(GameEvent* gameEvent);

	std::shared_ptr<GameEvent> popEvent();

	bool empty();

private:
	std::queue<std::shared_ptr<GameEvent>> events_;
};

#endif
