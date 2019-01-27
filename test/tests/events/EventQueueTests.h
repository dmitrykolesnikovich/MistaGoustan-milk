#ifndef MILK_EVENT_QUEUE_TESTS_H
#define MILK_EVENT_QUEUE_TESTS_H

// google test
#include "gtest/gtest.h"

// sut
#include "events/EventQueue.h"

#include "mocks/events/MGameEvent.h"

class EventQueueTests : public ::testing::Test {};

TEST_F(EventQueueTests, Ctor_Constructs) {
    ASSERT_NO_THROW(milk::EventQueue());
}

TEST_F(EventQueueTests, PushEvent_PushesEvent) {
    // Arrange
    milk::EventQueue eventQueue;

    // Act
    eventQueue.pushEvent<MGameEvent>();

    // Assert
    auto event = eventQueue.pollEvent();

    ASSERT_NE(nullptr, event);
}

TEST_F(EventQueueTests, PollEvents_PollsEventsInOrderOfPriority) {
    // Arrange
    milk::EventQueue eventQueue;

    // Act

    // Push in reverse order
    // FIFO - so 1 should pop out first
    // BUT the event queue is prioritized ;)
    eventQueue.pushEvent<MGameEventPriority1>();
    eventQueue.pushEvent<MGameEventPriority2>();

    // Assert
    auto e1 = eventQueue.pollEvent();
    ASSERT_EQ(2, (int)e1->type());
    auto e2 = eventQueue.pollEvent();
    ASSERT_EQ(1, (int)e2->type());
}

#endif
