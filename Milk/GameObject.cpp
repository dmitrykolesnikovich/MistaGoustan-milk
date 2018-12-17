#include "GameObject.h"

#include "ResourceManager.h"

GameObject::GameObject(const std::string& textureName)
	: _textureName(textureName)
{
}

GameObject::~GameObject()
{
}

void GameObject::load(ResourceManager& resourceManager)
{
	_texture = resourceManager.loadTexture(_textureName);
}

void GameObject::begin()
{
}

void GameObject::handleEvent(SDL_Event& e)
{
}

void GameObject::update()
{
}

void GameObject::end()
{
}

Texture* GameObject::getTexture() const
{
	return _texture;
}

int GameObject::getX() const
{
	return _xPosition;
}

int GameObject::getY() const
{
	return _yPosition;
}

void GameObject::setX(int x)
{
	_xPosition = x;
}

void GameObject::setY(int y)
{
	_yPosition = y;
}

int GameObject::getId() const
{
	return _id;
}
