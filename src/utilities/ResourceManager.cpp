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

std::string ResourceManager::loadFile(const std::string& filename)
{
	std::string path = rootDir_ + "/" + filename;
	SDL_RWops* rwops = SDL_RWFromFile(path.c_str(), "r");

	if (rwops == nullptr) 
		return nullptr;

	Sint64 fileSize = SDL_RWsize(rwops);

	char* fileContents = (char*)std::malloc(fileSize + 1);

	Sint64 readTotal = 0;
	Sint64 read = 1;

	char* buffer = fileContents;

	while (readTotal < fileSize && read != 0) 
	{
		read = SDL_RWread(rwops, buffer, 1, (fileSize - readTotal));

		readTotal += read;
		buffer += read;
	}

	SDL_RWclose(rwops);

	if (readTotal != fileSize) 
	{
		free(fileContents);
		return nullptr;
	}

	fileContents[readTotal] = '\0';

	return std::string(fileContents);
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
