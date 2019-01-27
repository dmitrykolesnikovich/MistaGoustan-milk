#ifndef MILK_GAME_EVENTS_H
#define MILK_GAME_EVENTS_H

#include <string>

namespace milk {
    class Actor;

    class BoxCollider;

    enum class GameEventType {
        // Prioritized by greatest value.

        SCENE_CHANGED,
        SCENE_LOADED,

        // Actor events
        ACTOR_COLLISION,
        ACTOR_TRIGGER,
        ACTOR_DETROYED,
        ACTOR_SPAWNED
    };

    // Base class for all game events.
    class GameEvent {
    public:
        virtual ~GameEvent() = default;

        virtual GameEventType type() const = 0;
    };

    class ActorSpawnedEvent : public GameEvent {
    public:
        explicit ActorSpawnedEvent(Actor& actor)
                : actor_(actor) {
        }

        GameEventType type() const override { return GameEventType::ACTOR_SPAWNED; }

        Actor& actor() { return actor_; }

    private:
        Actor& actor_;
    };

    class ActorDestroyedEvent : public GameEvent {
    public:
        explicit ActorDestroyedEvent(Actor& actor)
                : actor_(actor) {
        }

        GameEventType type() const override { return GameEventType::ACTOR_DETROYED; }

        Actor& actor() { return actor_; }

    private:
        Actor& actor_;
    };

    class ActorCollisionEvent : public GameEvent {
    public:
        ActorCollisionEvent(Actor& actor, BoxCollider& collider)
                : actor_(actor), otherCollider_(collider) {
        }

        GameEventType type() const override { return GameEventType::ACTOR_COLLISION; }

        Actor& actor() { return actor_; }

        BoxCollider& collider() { return otherCollider_; }

    private:
        Actor& actor_;
        BoxCollider& otherCollider_;
    };

    class SceneChangedEvent : public GameEvent {
    public:
        explicit SceneChangedEvent(const std::string& scene)
                : sceneToLoad_(scene) {
        }

        GameEventType type() const override { return GameEventType::SCENE_CHANGED; }

        std::string sceneToLoad() { return sceneToLoad_; }

    private:
        std::string sceneToLoad_;
    };

    class SceneLoadedEvent : public GameEvent {
    public:
        explicit SceneLoadedEvent(const std::string& scene)
                : sceneLoaded_(scene) {
        }

        GameEventType type() const override { return GameEventType::SCENE_LOADED; }

        std::string sceneLoaded() { return sceneLoaded_; }

    private:
        std::string sceneLoaded_;
    };
}

#endif
