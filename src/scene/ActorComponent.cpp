#include "ActorComponent.h"

milk::ActorComponent::ActorComponent(milk::Actor& actor)
        : actor_(actor)
{
}

milk::Actor& milk::ActorComponent::actor() const
{
    return actor_;
}
