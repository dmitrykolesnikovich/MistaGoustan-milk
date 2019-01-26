#ifndef _SCENE_TESTS_H
#define _SCENE_TESTS_H

// google test
#include "gtest/gtest.h"

#include "core/Actor.h"
#include "core/Scene.h"

#include "systems/events/EventQueue.h"
#include "systems/events/GameEvents.h"

class SceneTests : public ::testing::Test {};

TEST_F(SceneTests, Ctor_Constructs) {
    // Arrange
    EventQueue eventQueue;

    // Act & Assert
    ASSERT_NO_THROW(Scene(eventQueue, 640, 360));
}

TEST_F(SceneTests, SpawnActor_SpawnsActor) {
    // Arrange
    EventQueue eventQueue;

    Scene scene{eventQueue, 640, 360};

    // Act
    auto actor = scene.spawnActor("steve");

    // Assert
    ASSERT_NE(nullptr, actor);
}

TEST_F(SceneTests, SpawnActor_SetsActorName) {
    // Arrange
    EventQueue eventQueue;

    Scene scene{eventQueue, 640, 360};

    // Act
    auto actor = scene.spawnActor("steve");

    // Assert
    ASSERT_EQ("steve", actor->name());
}

TEST_F(SceneTests, SpawnActor_SetsActorId) {
    // Arrange
    EventQueue eventQueue;

    Scene scene{eventQueue, 640, 360};

    // Act
    auto waddap = scene.spawnActor("waddap");
    auto boi = scene.spawnActor("boi");
    auto ahaha = scene.spawnActor("ahaha");

    // Assert
    ASSERT_EQ(0, waddap->id());
    ASSERT_EQ(1, boi->id());
    ASSERT_EQ(2, ahaha->id());
}

TEST_F(SceneTests, SpawnActor_GeneratesActorSpawnedEvent) {
    // Arrange
    EventQueue eventQueue;

    Scene scene{eventQueue, 640, 360};

    auto actor = scene.spawnActor("steve");

    // Act
    auto spawnedEvent = eventQueue.pollEvent();

    // Assert
    ASSERT_NE(nullptr, spawnedEvent);
    ASSERT_TRUE(spawnedEvent->type() == GameEventType::ACTOR_SPAWNED);

    auto& spawnedEventActor = (dynamic_cast<ActorSpawnedEvent*>(spawnedEvent))->actor();

    ASSERT_EQ(actor, &spawnedEventActor);
}

TEST_F(SceneTests, DestroyActor_GivenActorDoesntExist_DoesNotGenerateActorDestroyedEvent) {
    // Arrange
    EventQueue eventQueue;

    Scene scene{eventQueue, 640, 360};

    // Act
    scene.destroyActor(76);

    auto destroyedEvent = eventQueue.pollEvent();

    // Assert
    ASSERT_EQ(nullptr, destroyedEvent);
}

TEST_F(SceneTests, DestroyActor_GeneratesActorDestroyedEvent) {
    // Arrange
    EventQueue eventQueue;

    Scene scene{eventQueue, 640, 360};

    auto actor = scene.spawnActor("steve");

    // Lets get rid of that spawned event
    eventQueue.pollEvent();

    // Act
    scene.destroyActor(actor->id());

    // Assert
    auto destroyedEvent = eventQueue.pollEvent();

    ASSERT_TRUE(destroyedEvent->type() == GameEventType::ACTOR_DETROYED);

    auto& destroyedEventActor = (dynamic_cast<ActorDestroyedEvent*>(destroyedEvent))->actor();

    ASSERT_EQ(actor, &destroyedEventActor);
}

TEST_F(SceneTests, FindActor_FindsActor) {
    // Arrange
    EventQueue eventQueue;

    Scene scene{eventQueue, 640, 360};

    auto actor = scene.spawnActor("steve");

    scene.syncActorLists();

    // Act
    auto foundActor = scene.findActor("steve");

    // Assert
    ASSERT_EQ(actor, foundActor);
}

TEST_F(SceneTests, FindActor_GivenActorDoesntExist_DoesNotFindActor) {
    // Arrange
    EventQueue eventQueue;

    Scene scene{eventQueue, 640, 360};

    // Act
    auto foundActor = scene.findActor("steve");

    // Assert
    ASSERT_EQ(nullptr, foundActor);
}

#endif
