#ifndef _MACTOR_COMPONENT_
#define _MACTOR_COMPONENT_

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
