#include "TextureLoader.h"

#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "graphics/Texture.h"

milk::TextureLoader::TextureLoader(SDL_Renderer& sdlRenderer, const std::string& rootDir)
        : AssetLoader(rootDir),
          sdlRenderer_(sdlRenderer)
{

}

std::shared_ptr<milk::Texture> milk::TextureLoader::load(const std::string& textureName)
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

void milk::TextureLoader::unload()
{
    auto textureItr = textureCache_.begin();

    while (textureItr != textureCache_.end())
    {
        if (textureItr->second.use_count() == 0)
            textureCache_.erase(textureItr->first);

        textureItr++;
    }
}
