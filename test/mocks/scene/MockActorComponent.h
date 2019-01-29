#ifndef MILK_MOCK_ACTOR_COMPONENT_H
#define MILK_MOCK_ACTOR_COMPONENT_H

#include "scene/ActorComponent.h"

class MockActorComponent : public milk::ActorComponent
{
public:
    static milk::ComponentType type;

    explicit MockActorComponent(milk::Actor& actor)
            : ActorComponent(actor)
    {
    }
};

milk::ComponentType MockActorComponent::type = milk::ComponentType::MAX_COMPONENTS;

#endif
