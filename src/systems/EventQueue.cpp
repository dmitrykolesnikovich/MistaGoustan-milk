#include "EventQueue.h"

void EventQueue::pushEvent(GameEvent* gameEvent)
{
	events_.push(std::shared_ptr<GameEvent>(gameEvent));
}

std::shared_ptr<GameEvent> EventQueue::popEvent()
{
	auto e = events_.front();
	events_.pop();
	return e;
}

bool EventQueue::empty()
{
	return events_.empty();
}
