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

	Texture* loadTexture(const std::string& name);

	void unloadTextures();

private:
	SDL_Renderer* _renderer;

	std::unordered_map<std::string, Texture*> _textureCache;
};

#endif
