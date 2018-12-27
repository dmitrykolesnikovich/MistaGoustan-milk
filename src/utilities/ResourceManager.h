#ifndef _RESOURCE_MANAGER_
#define _RESOURCE_MANAGER_

#include <unordered_map>
#include <string>

struct SDL_Renderer;

class Texture;

class ResourceManager
{
public:
	ResourceManager(SDL_Renderer* renderer);
	~ResourceManager();

	// Load texture. Textures are cached.
	Texture* loadTexture(const std::string& name);

	// Unload all loaded textures.
	void unloadTextures();

private:
	SDL_Renderer* sdlRenderer_;

	std::unordered_map<std::string, Texture*> textureCache_;
};

#endif
