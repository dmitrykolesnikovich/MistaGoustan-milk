#include "Actor.h"

Actor::Actor(Scene& scene)
	: _scene(scene)
{
}

Actor::~Actor()
{
}

int Actor::getId() const
{
	return _id;
}

std::string Actor::getName() const
{
	return _name;
}

Vector2d Actor::getPosition() const
{
	return _position;
}

void Actor::setPosition(float x, float y)
{
	_position.x = x;
	_position.y = y;
}

void Actor::setPosition(Vector2d position)
{
	_position.x = position.x;
	_position.y = position.y;
}

void Actor::load(ResourceManager& resourceManager)
{
	for (auto& it : _componentsByType) 
	{
		it.second->load(resourceManager);
	}
}
