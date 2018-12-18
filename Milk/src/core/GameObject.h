#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_

#include <string>

#include "../math/Vector2d.h"

union SDL_Event;

class ResourceManager;
class Texture;

class GameObject
{
public:
	friend class Level;

	GameObject(const std::string& textureName);
	~GameObject();

	// The position of the game object. For movement, modify velocity.
	Vector2d position;

	// The velocity of the game object.
	Vector2d velocity;

	// Load the game objects resources.
	virtual void load(ResourceManager& resourceManager);

	// Called at the beginning of the game objects life cycle.
	virtual void begin();

	// Called when input events a polled.
	virtual void handleEvent(SDL_Event& e);

	// Called once per frame.
	virtual void update();

	// Called at the end of the game objects life cycle.
	virtual void end();

	// Get the game objects texture.
	Texture* getTexture() const;

	// Get the game objects id.
	int getId() const;

private:
	unsigned int _id;

	std::string _textureName;
	Texture* _texture;
};

#endif
