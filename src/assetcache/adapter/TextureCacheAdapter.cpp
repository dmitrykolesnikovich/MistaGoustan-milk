#include "TextureCacheAdapter.h"

#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "graphics/Texture.h"

milk::adapter::TextureCacheAdapter::TextureCacheAdapter(SDL_Renderer& sdlRenderer, const std::string& rootDir)
        : AssetCache(rootDir),
          sdlRenderer_(sdlRenderer)
{
}

bool milk::adapter::TextureCacheAdapter::init()
{
    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;

    if ((IMG_Init(imgFlags) & imgFlags) != imgFlags)
    {
        std::cout << "Error initializing SDL_image: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

std::shared_ptr<milk::Texture> milk::adapter::TextureCacheAdapter::load(const std::string& textureName)
{
    auto found = textureCache_.find(textureName);

    if (found != textureCache_.end())
        return found->second;

    auto sdlSurface = IMG_Load(getPath(textureName).c_str());

    if (sdlSurface == nullptr)
    {
        std::cout << "Error loading image: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    auto sdlTexture = SDL_CreateTextureFromSurface(&sdlRenderer_, sdlSurface);

    SDL_FreeSurface(sdlSurface);

    int width;
    int height;

    SDL_QueryTexture(sdlTexture, nullptr, nullptr, &width, &height);

    auto pTexture = std::make_shared<Texture>(sdlTexture, width, height);

    textureCache_.insert(std::make_pair(textureName, pTexture));

    return pTexture;
}

void milk::adapter::TextureCacheAdapter::freeUnreferencedAssets()
{
    auto textureItr = textureCache_.begin();

    while (textureItr != textureCache_.end())
    {
        if (textureItr->second.use_count() == 0)
            textureCache_.erase(textureItr->first);

        textureItr++;
    }
}

void milk::adapter::TextureCacheAdapter::free()
{
    textureCache_.clear();
    IMG_Quit();
}
