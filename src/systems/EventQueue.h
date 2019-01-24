#ifndef _EVENT_QUEUE_H
#define _EVENT_QUEUE_H

#include <queue>
#include <vector>

#include "GameEvents.h"

// Used to prioritize game events by greatest value.
struct GameEventComparison {
    bool operator()(const GameEvent* first, const GameEvent* second) const {
        return first->type() < second->type();
    }
};

// The game's event queue.
// Events should be created frugally.
// Events should mainly exist if the request needs to be deferred until the next frame.
class EventQueue {
public:
    EventQueue();

    // Pushes the new event into the queue.
    template<typename TEvent, typename... Args>
    void pushEvent(Args&& ... args) {
        events_.push(new TEvent(std::forward<Args>(args)...));
    }

    // Polls the next event. Returns nullptr when queue is empty.
    GameEvent* pollEvent();

private:
    std::priority_queue<GameEvent*, std::vector<GameEvent*>, GameEventComparison> events_;
    GameEvent* lastPoppedEvent_;
};


#endif
