#ifndef MILK_MOCK_GAME_EVENT_H
#define MILK_MOCK_GAME_EVENT_H

// Google mock
#include "gmock/gmock.h"

#include "events/GameEvents.h"

class MockGameEvent : public milk::GameEvent
{
public:
    MOCK_CONST_METHOD0(type, milk::GameEventType());
};

class MGameEventPriority1 : public milk::GameEvent
{
public:
    milk::GameEventType type() const override
    {
        return (milk::GameEventType)1;
    }
};

class MGameEventPriority2 : public milk::GameEvent
{
public:
    milk::GameEventType type() const override
    {
        return (milk::GameEventType)2;
    }
};

#endif
