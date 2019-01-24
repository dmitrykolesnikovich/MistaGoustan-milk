#include "ActorComponent.h"

ActorComponent::ActorComponent(Actor& actor)
        : actor_(actor) {
}

Actor& ActorComponent::actor() const {
    return actor_;
}
