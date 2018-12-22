#include "Actor.h"

Actor::Actor(Game& game)
	: _game(game)
{
}

Actor::~Actor()
{
}

bool Actor::removeComponent(ComponentType type)
{
	if ((_componentBitmask & type) != type)
		return false;

	_componentBitmask &= ~type;

	_componentsByType.erase(type);

	return true;
}
