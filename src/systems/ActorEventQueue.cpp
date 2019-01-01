#include "ActorEventQueue.h"

void ActorEventQueue::pushEvent(ActorEvent* gameEvent)
{
	events_.push(std::shared_ptr<ActorEvent>(gameEvent));
}

std::shared_ptr<ActorEvent> ActorEventQueue::popEvent()
{
	auto e = events_.top();
	events_.pop();

	return e;
}

bool ActorEventQueue::empty()
{
	return events_.empty();
}
