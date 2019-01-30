#include "EventQueue.h"

milk::EventQueue::EventQueue()
        : lastPoppedEvent_(nullptr)
{
}

milk::GameEvent* milk::EventQueue::poll()
{
    if (lastPoppedEvent_ != nullptr)
    {
        delete lastPoppedEvent_;
        lastPoppedEvent_ = nullptr;
    }

    if (events_.empty())
        return nullptr;

    lastPoppedEvent_ = events_.top();
    events_.pop();

    return lastPoppedEvent_;
}
