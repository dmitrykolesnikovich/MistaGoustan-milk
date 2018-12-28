#ifndef _ACTOR_
#define _ACTOR_

#include <memory>
#include <string>
#include <unordered_map>

#include "ActorComponent.h"

#include "../math/Vector2d.h"

class ResourceManager;
class Scene;

class Actor
{
public:
	friend class Scene;

	Actor(Scene& scene);
	~Actor();

	// Returns the actors unique id.
	int id() const;

	// Returns the actors name.
	std::string getName() const;

	// Returns the actors position.
	Vector2d position() const;

	// Sets the actors position.
	void position(float x, float y);

	// Sets the actors position.
	void position(Vector2d position);

	// Attempts to add a component of the given type.
	// Returns true if successful.
	template <class TComponent>
	bool addComponent() 
	{
		ComponentType type = TComponent::type;

		if ((componentBitmask_ & type) == type)
			return false;

		componentBitmask_ |= type;

		componentsByType_.insert(std::make_pair(type, std::unique_ptr<ActorComponent>(new TComponent(*this))));

		return true;
	}
	
	// Attempts to get a component of the given type.
	// Returns nullptr if no component is found.
	template <class TComponent>
	TComponent* getComponent() const
	{
		ComponentType type = TComponent::type;

		if ((componentBitmask_ & type) != type)
			return nullptr;

		auto& component = componentsByType_.at(type);

		return dynamic_cast<TComponent*>(component.get());
	}

	// Attempts to remove a component of the given type.
	// Returns true if successful.
	template <class TComponent>
	bool removeComponent() 
	{
		ComponentType type = TComponent::type;

		if ((componentBitmask_ & type) != type)
			return false;

		componentBitmask_ &= ~type;

		componentsByType_.erase(type);

		return true;
	}

private:
	int id_;
	std::string name_;
	Vector2d position_;
	uint32_t componentBitmask_;

	Scene& scene_;

	std::unordered_map<ComponentType, std::unique_ptr<ActorComponent>> componentsByType_;
};

#endif

