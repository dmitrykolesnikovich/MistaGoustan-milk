#include "ResourceManager.h"

#include "SDL.h"
#include "SDL_image.h"

#include <unordered_map>
#include <string>
#include <iostream>

#include "Texture.h"

ResourceManager::ResourceManager(const std::string& rootDir)
	: rootDir_(rootDir)
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
	auto& found = textureCache_.find(name);
	
	if (found != textureCache_.end())
		return found->second;

	std::string resourcePath = rootDir_ + "/" + name;

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

	textureCache_.insert(std::make_pair(name, texture));

	return texture;
}

void ResourceManager::unloadTextures()
{
	for (auto it = textureCache_.begin(); it != textureCache_.end(); ++it) 
	{
		delete it->second;
		it->second = nullptr;
	}

	textureCache_.clear();
}

void ResourceManager::freeResources()
{
	unloadTextures();
}
