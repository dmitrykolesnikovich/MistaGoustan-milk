#include "EventQueue.h"

EventQueue::EventQueue()
        : lastPoppedEvent_(nullptr) {
}

GameEvent* EventQueue::pollEvent() {
    if (lastPoppedEvent_ != nullptr) {
        delete lastPoppedEvent_;
        lastPoppedEvent_ = nullptr;
    }

    if (events_.empty())
        return nullptr;

    lastPoppedEvent_ = events_.top();
    events_.pop();

    return lastPoppedEvent_;
}
