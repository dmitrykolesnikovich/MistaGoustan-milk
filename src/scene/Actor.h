#ifndef MILK_ACTOR_H
#define MILK_ACTOR_H

#include <memory>
#include <string>
#include <unordered_map>

#include "math/Vector2d.h"

namespace milk
{
    class ActorComponent;

    class ResourceManager;

    // An actor is an object that exists within a scene.
    // An actor can range from a rock on the ground to a dragon boss monster.
    // Attach components to an actor in order to define it and give it behavior.
    class Actor
    {
    public:
        Actor(int id, const std::string& name, const Vector2d& position);

        ~Actor() = default;

        // Returns the actor's unique id.
        int id() const;

        // Returns the actor's name.
        std::string name() const;

        // Returns the actor's position.
        Vector2d position() const;

        // Sets the actor's position.
        void position(float x, float y);

        // Returns the added component and nullptr if addition fails.
        template<class TComponent, typename... Args>
        TComponent* addComponent(Args&& ... args)
        {
            auto type = TComponent::type;

            if ((componentBitmask_ & type) == type)
                return nullptr;

            componentBitmask_ |= type;

            auto component = new TComponent(*this, std::forward<Args>(args)...);

            componentsByType_.insert(std::make_pair(type, std::unique_ptr<ActorComponent>(component)));

            return component;
        }

        // Returns component of the given type and nullptr if not found.
        template<class TComponent>
        TComponent* getComponent() const
        {
            auto type = TComponent::type;

            if ((componentBitmask_ & type) != type)
                return nullptr;

            auto& component = componentsByType_.at(type);

            return dynamic_cast<TComponent*>(component.get());
        }

    private:
        int id_;
        std::string name_;
        Vector2d position_;
        uint32_t componentBitmask_;

        std::unordered_map<int, std::unique_ptr<ActorComponent>> componentsByType_;
    };
}

#endif

