#pragma once

#include <unordered_map>
#include <string>

#include <SDL_assert.h>

struct SDL_Renderer;
class Texture;

class ResourceManager
{
public:
	~ResourceManager();
	
	static void init(SDL_Renderer* renderer);

	static ResourceManager& getInstance();

	Texture* loadTexture(const std::string& name);

	void unloadTextures();

private:
	ResourceManager() {}

	static bool _initialized;

	static SDL_Renderer* _renderer;

	std::unordered_map<std::string, Texture*> _textureCache;
};
