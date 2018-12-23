#pragma once

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
	std::string _textureName;
	Texture* _texture;
	SDL_Rect _sourceRect;
};