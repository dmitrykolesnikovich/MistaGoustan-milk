#include "ResourceManager.h"

#include "SDL.h"
#include "SDL_image.h"

#include <unordered_map>
#include <string>
#include <iostream>

#include "Texture.h"

ResourceManager::ResourceManager(const std::string& rootDir)
	: root(rootDir)
	, sdlRenderer_(nullptr)
{
}

ResourceManager::~ResourceManager()
{
	freeResources();
}

void ResourceManager::init(SDL_Renderer* sdlRenderer)
{
	sdlRenderer_ = sdlRenderer;
}

Texture* ResourceManager::loadTexture(const std::string& name)
{
	std::unordered_map<std::string, Texture*>::const_iterator found = textureCache_.find(name);
	
	if (found != textureCache_.end())
		return found->second;

	std::string resourcePath = root + "/" + name;

	SDL_Surface* surf = IMG_Load(resourcePath.c_str());

	if (surf == nullptr) 
	{
		std::cout << "Error loading image: " << IMG_GetError() << std::endl;
		return nullptr;
	}

	SDL_Texture* sdlTex = SDL_CreateTextureFromSurface(sdlRenderer_, surf);

	SDL_FreeSurface(surf);

	int width;
	int height;

	SDL_QueryTexture(sdlTex, nullptr, nullptr, &width, &height);

	Texture* texture = new Texture(sdlTex, width, height);

	std::pair<std::string, Texture*> loadedTexture(name, texture);

	textureCache_.insert(loadedTexture);

	return texture;
}

void ResourceManager::unloadTextures()
{
	for (auto it = textureCache_.begin(); it != textureCache_.end(); ++it) 
	{
		delete it->second;
		it->second = nullptr;
	}
}

void ResourceManager::freeResources()
{
	unloadTextures();
}
