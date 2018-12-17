#pragma once

#include <string>

#include "Vector2d.h"

union SDL_Event;

class ResourceManager;
class Texture;

class GameObject
{
public:
	friend class Level;

	GameObject(const std::string& textureName);
	~GameObject();

	Vector2d position;
	Vector2d velocity;

	virtual void load(ResourceManager& resourceManager);

	virtual void begin();
	virtual void handleEvent(SDL_Event& e);
	virtual void update();
	virtual void end();

	Texture* getTexture() const;

	int getId() const;

private:
	unsigned int _id;

	std::string _textureName;
	Texture* _texture;


};
