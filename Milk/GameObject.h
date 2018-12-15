#pragma once

#include <string>

class ResourceManager;
class Texture;

union SDL_Event;

class GameObject
{
public:
	friend class Level;

	GameObject(const std::string& textureName);
	~GameObject();

	virtual void load(ResourceManager& resourceManager);

	virtual void begin();
	virtual void handleEvent(SDL_Event& e);
	virtual void update();
	virtual void end();

	Texture* getTexture() const;
	int getX() const;
	int getY() const;

	int getId() const;

protected:
	int _xPosition;
	int _yPosition;

	float _xVelocity;
	float _yVelocity;

private:
	unsigned int _id;

	std::string _textureName;
	Texture* _texture;
};
