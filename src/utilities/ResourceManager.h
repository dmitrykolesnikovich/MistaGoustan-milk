#ifndef _RESOURCE_MANAGER_
#define _RESOURCE_MANAGER_

#include <unordered_map>
#include <string>

struct SDL_Renderer;

class Texture;

class ResourceManager
{
public:
	ResourceManager(const std::string& rootDir = "");
	~ResourceManager();

	void init(SDL_Renderer* sdlRenderer);

	// Load texture. Textures are cached.
	Texture* loadTexture(const std::string& name);

	// Unload all loaded textures.
	void unloadTextures();

	// Frees all loaded resources.
	void freeResources();

private:
	std::string root;

	SDL_Renderer* sdlRenderer_;

	std::unordered_map<std::string, Texture*> textureCache_;
};

#endif
