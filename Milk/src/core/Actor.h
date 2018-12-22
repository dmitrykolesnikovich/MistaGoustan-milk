#ifndef _ACTOR_
#define _ACTOR_

#include <memory>
#include <string>
#include <unordered_map>

#include "ActorComponent.h"

class Scene;

class Actor
{
public:
	friend class Scene;

	Actor(Scene& scene);
	~Actor();

	std::string getName() const;

	template <class TComponent>
	bool addComponent(ComponentType type) 
	{
		if ((_componentBitmask & type) == type)
			return false;

		_componentBitmask |= type;

		_componentsByType.insert(std::make_pair(type, std::unique_ptr<ActorComponent>(new TComponent(*this))));

		return true;
	}
	
	template <class TComponent>
	TComponent* getComponent(ComponentType type) 
	{
		if ((_componentBitmask & type) != type)
			return nullptr;

		auto& component = _componentsByType.at(type);

		return dynamic_cast<TComponent*>(component.get());
	}

	bool removeComponent(ComponentType type);

private:
	int _id;
	std::string _name;
	uint32_t _componentBitmask;

	Scene& _scene;

	std::unordered_map<ComponentType, std::unique_ptr<ActorComponent>> _componentsByType;
};

#endif

