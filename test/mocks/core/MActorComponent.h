#ifndef MILK_MACTOR_COMPONENT_H
#define MILK_MACTOR_COMPONENT_H

#include "core/ActorComponent.h"

class MActorComponent : public milk::ActorComponent {
public:
    static milk::ComponentType type;

    explicit MActorComponent(milk::Actor& actor)
            : ActorComponent(actor) {
    }
};

milk::ComponentType MActorComponent::type = milk::ComponentType::MAX_COMPONENTS;

#endif
