#ifndef _ACTOR_
#define _ACTOR_

#include <memory>
#include <string>
#include <unordered_map>

#include "ActorComponent.h"

#include "../math/Vector2d.h"

class ResourceManager;
class Scene;

// An object that exists within the current scene.
// An actor can range from a rock on the ground to a dragon boss monster.
// Attach components to an actor in order to define it and give it behavior.
class Actor
{
public:
	Actor(Scene& scene, int id, const std::string& name, const Vector2d& position);
	~Actor() = default;

	// Returns the actors scene.
	Scene& scene() const;

	// Returns the actors unique id.
	int id() const;

	// Returns the actors name.
	std::string name() const;

	// Returns the actors position.
	Vector2d position() const;

	// Sets the actors position.
	void position(float x, float y);

	// Sets the actors position.
	void position(Vector2d position);

	// Returns the added component and nullptr if addition failed.
	template <class TComponent>
	TComponent* addComponent() 
	{
		ComponentType type = TComponent::type;

		if ((componentBitmask_ & type) == type)
			return nullptr;

		componentBitmask_ |= type;

		auto rawPtr = new TComponent(*this);

		componentsByType_.insert(std::make_pair(type, std::unique_ptr<ActorComponent>(rawPtr)));

		return rawPtr;
	}
	
	// Returns component of the given type and nullptr if not found.
	template <class TComponent>
	TComponent* getComponent() const
	{
		ComponentType type = TComponent::type;

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

	Scene& scene_;

	std::unordered_map<int, std::unique_ptr<ActorComponent>> componentsByType_;
};

#endif

