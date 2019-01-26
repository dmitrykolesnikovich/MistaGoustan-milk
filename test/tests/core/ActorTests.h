#ifndef _ACTOR_TESTS_
#define _ACTOR_TESTS_

// google test
#include "gtest/gtest.h"

// sut
#include "core/Actor.h"

// mocks
#include "mocks/core/MActorComponent.h"

class ActorTests : public ::testing::Test {};

TEST_F(ActorTests, Ctor_Constructs)
{
    // Act & Assert
    ASSERT_NO_THROW(Actor(1, "steve", {0, 0}));
}

TEST_F(ActorTests, Id_ReturnsId)
{
    // Arrange
    int expectedId = 1;

    Actor actor{expectedId, "steve", {0, 0}};

    // Act
    auto id = actor.id();

    // Assert
    ASSERT_EQ(expectedId, id);
}

TEST_F(ActorTests, Name_ReturnsName)
{
    // Arrange
    std::string expectedName = "steve";

    Actor actor{1, expectedName, {0, 0}};

    // Act
    auto name = actor.name();

    // Assert
    ASSERT_EQ(expectedName, name);
}

TEST_F(ActorTests, Position_ReturnsPosition)
{
    // Arrange
    Vector2d expectedPosition = {1, 1};

    Actor actor{ 1, "steve", expectedPosition};

    // Act
    auto position = actor.position();

    // Assert
    ASSERT_TRUE(expectedPosition == position);
}

TEST_F(ActorTests, Position_SetsPosition)
{
    // Arrange
    Actor actor{1, "steve", {0, 0}};

    // Act
    actor.position(5, 7);

    // Assert
    ASSERT_TRUE(actor.position() == Vector2d(5, 7));
}

TEST_F(ActorTests, AddComponent_ReturnsNewlyAddedComponent)
{
    // Arrange
    Actor actor{1, "steve", {0, 0}};

    // Act
    auto component = actor.addComponent<MActorComponent>();

    // Assert
    ASSERT_NE(nullptr, component);
}

TEST_F(ActorTests, AddComponent_DoesNotAddSameComponentTypeTwice)
{
    // Arrange
    Actor actor{1, "steve", {0, 0}};

    actor.addComponent<MActorComponent>();

    // Act
    auto component = actor.addComponent<MActorComponent>();

    // Assert
    ASSERT_EQ(nullptr, component);
}

TEST_F(ActorTests, GetComponent_GivenComponentExists_ReturnsComponent)
{
    // Arrange
    Actor actor{1, "steve", {0, 0}};

    actor.addComponent<MActorComponent>();

    // Act
    auto component = actor.getComponent<MActorComponent>();

    // Assert
    ASSERT_NE(nullptr, component);
}

TEST_F(ActorTests, GetComponent_GivenNoComponentExists_ReturnsNoComponent)
{
    // Arrange
    Actor actor{1, "steve", {0, 0}};

    // Act
    auto component = actor.getComponent<MActorComponent>();

    // Assert
    ASSERT_EQ(nullptr, component);
}

#endif