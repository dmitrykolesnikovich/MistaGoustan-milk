#ifndef _MACTOR_COMPONENT_H
#define _MACTOR_COMPONENT_H

#include "core/ActorComponent.h"

class MActorComponent : public ActorComponent
{
public:
    static ComponentType type;

    explicit MActorComponent(Actor& actor)
        : ActorComponent(actor)
    {
    }
};

ComponentType MActorComponent::type = ComponentType ::MAX_COMPONENTS;

#endif
