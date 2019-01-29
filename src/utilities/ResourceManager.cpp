#include "ResourceManager.h"

#include <unordered_map>
#include <string>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "graphics/Texture.h"

milk::ResourceManager::ResourceManager(const std::string& rootDir)
        : rootDir_(rootDir),
          sdlRenderer_(nullptr)
{
}

milk::ResourceManager::~ResourceManager()
{
    freeResources();
}

void milk::ResourceManager::init(SDL_Renderer* sdlRenderer)
{
    sdlRenderer_ = sdlRenderer;
}

milk::Texture* milk::ResourceManager::loadTexture(const std::string& name)
{
    auto found = textureCache_.find(name);

    if (found != textureCache_.end())
        return found->second;

    std::string resourcePath = rootDir_ + "/" + name;

    auto surf = IMG_Load(resourcePath.c_str());

    if (surf == nullptr)
    {
        std::cout << "Error loading image: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    auto sdlTex = SDL_CreateTextureFromSurface(sdlRenderer_, surf);

    SDL_FreeSurface(surf);

    int width;
    int height;

    SDL_QueryTexture(sdlTex, nullptr, nullptr, &width, &height);

    auto texture = new Texture(sdlTex, width, height);

    textureCache_.insert(std::make_pair(name, texture));

    return texture;
}

std::string milk::ResourceManager::loadFile(const std::string& filename)
{
    std::string path = rootDir_ + "/" + filename;

    auto rwops = SDL_RWFromFile(path.c_str(), "r");

    if (rwops == nullptr)
        return nullptr;

    Sint64 fileSize = SDL_RWsize(rwops);

    auto fileContents = (char*)std::malloc((size_t)(fileSize + 1));

    Sint64 readTotal = 0;
    Sint64 read = 1;

    char* buffer = fileContents;

    while (readTotal < fileSize && read != 0)
    {
        read = SDL_RWread(rwops, buffer, 1, ((size_t)(fileSize - readTotal)));

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

void milk::ResourceManager::unloadTextures()
{
    for (auto& it : textureCache_)
    {
        delete it.second;
        it.second = nullptr;
    }

    textureCache_.clear();
}

void milk::ResourceManager::freeResources()
{
    unloadTextures();
}
