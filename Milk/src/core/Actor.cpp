#include "Actor.h"

Actor::Actor(Scene& scene)
	: _scene(scene)
{
}

Actor::~Actor()
{
}

std::string Actor::getName() const
{
	return _name;
}

bool Actor::removeComponent(ComponentType type)
{
	if ((_componentBitmask & type) != type)
		return false;

	_componentBitmask &= ~type;

	_componentsByType.erase(type);

	return true;
}
