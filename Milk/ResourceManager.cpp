#include "ResourceManager.h"

#include <SDL.h>
#include <SDL_image.h>

#include <unordered_map>
#include <string>
#include <iostream>

#include "Texture.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	unloadTextures();
}

void ResourceManager::init(SDL_Renderer* renderer)
{
	_renderer = renderer;
}

Texture* ResourceManager::loadTexture(const std::string& name)
{
	std::unordered_map<std::string, Texture*>::const_iterator found = _textureCache.find(name);
	
	if (found != _textureCache.end())
		return found->second;

	SDL_Surface* surf = IMG_Load(name.c_str());

	if (surf == nullptr) 
	{
		std::cout << "Error loading image: " << IMG_GetError() << std::endl;
		return nullptr;
	}

	SDL_Texture* sdlTex = SDL_CreateTextureFromSurface(_renderer, surf);

	SDL_FreeSurface(surf);

	int width;
	int height;

	SDL_QueryTexture(sdlTex, nullptr, nullptr, &width, &height);

	Texture* texture = new Texture(sdlTex, width, height);

	std::pair<std::string, Texture*> loadedTexture(name, texture);

	_textureCache.insert(loadedTexture);

	return texture;
}

void ResourceManager::unloadTextures()
{
	for (auto it = _textureCache.begin(); it != _textureCache.end(); ++it) 
	{
		delete it->second;
		it->second = nullptr;
	}
}
