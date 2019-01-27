#ifndef MILK_EVENT_QUEUE_TESTS_H
#define MILK_EVENT_QUEUE_TESTS_H

#include "gtest/gtest.h"

#include "mocks/events/MockGameEvent.h"

#include "events/EventQueue.h"

class EventQueueTests : public ::testing::Test {};

TEST_F(EventQueueTests, Ctor_Constructs) {
    ASSERT_NO_THROW(milk::EventQueue());
}

TEST_F(EventQueueTests, PushEvent_PushesEvent) {
    // Arrange
    milk::EventQueue eventQueue;

    // Act
    eventQueue.pushEvent<MockGameEvent>();

    // Assert
    auto event = eventQueue.pollEvent();

    ASSERT_NE(nullptr, event);
}

TEST_F(EventQueueTests, PollEvents_PollsEventsInOrderOfHighestPriority) {
    // Arrange
    milk::EventQueue eventQueue;

    // Act

    // Even though 1 is enqueued before 2, we should receive the events in order of highest priority.
    eventQueue.pushEvent<MGameEventPriority1>();
    eventQueue.pushEvent<MGameEventPriority2>();

    // Assert
    auto event1 = eventQueue.pollEvent();
    ASSERT_EQ(2, (int)event1->type());

    auto event2 = eventQueue.pollEvent();
    ASSERT_EQ(1, (int)event2->type());

    // Make sure to free all events.
    while (auto e = eventQueue.pollEvent()) {}
}

#endif
