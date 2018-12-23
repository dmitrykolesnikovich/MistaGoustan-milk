#ifndef _SPRITE_
#define _SPRITE_

#include <string>

#include <SDL.h>

#include "../core/ActorComponent.h"

class Texture;

class Sprite : public ActorComponent
{
public:
	static const ComponentType type;

	Sprite(Actor& actor);
	~Sprite();

	void load(ResourceManager& resourceManager);

	void setTextureName(const std::string& name);

	Texture* getTexture() const;

	void setSourceRect(int x, int y, int width, int height);

	void setSourceRect(SDL_Rect rect);

	SDL_Rect getSourceRect() const;

private:
	std::string textureName_;
	Texture* texture_;
	SDL_Rect sourceRect_;
};

#endif
