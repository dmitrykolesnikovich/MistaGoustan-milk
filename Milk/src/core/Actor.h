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

	int getId() const;

	std::string getName() const;

	Vector2d getPosition() const;

	void setPosition(float x, float y);

	void setPosition(Vector2d position);

	void load(ResourceManager& resourceManager);

	template <class TComponent>
	bool addComponent() 
	{
		ComponentType type = TComponent::type;

		if ((_componentBitmask & type) == type)
			return false;

		_componentBitmask |= type;

		_componentsByType.insert(std::make_pair(type, std::unique_ptr<ActorComponent>(new TComponent(*this))));

		return true;
	}
	
	template <class TComponent>
	TComponent* getComponent() 
	{
		ComponentType type = TComponent::type;

		if ((_componentBitmask & type) != type)
			return nullptr;

		auto& component = _componentsByType.at(type);

		return dynamic_cast<TComponent*>(component.get());
	}

	template <class TComponent>
	bool removeComponent() 
	{
		ComponentType type = TComponent::type;

		if ((_componentBitmask & type) != type)
			return false;

		_componentBitmask &= ~type;

		_componentsByType.erase(type);

		return true;
	}

private:
	int _id;
	std::string _name;
	Vector2d _position;
	uint32_t _componentBitmask;

	Scene& _scene;

	std::unordered_map<ComponentType, std::unique_ptr<ActorComponent>> _componentsByType;
};

#endif

