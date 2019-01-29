#ifndef MILK_TEXTURE_LOADER_H
#define MILK_TEXTURE_LOADER_H

#include <string>
#include <unordered_map>

#include "utilities/AssetLoader.h"

struct SDL_Renderer;

namespace milk
{
    class Texture;

    class TextureLoader : public AssetLoader<Texture>
    {
    public:
        TextureLoader(SDL_Renderer& sdlRenderer, const std::string& rootDir);

        // Loads the texture/fetches it from cache and returns it.
        std::shared_ptr<Texture> load(const std::string& textureName) override;

        // Invalidates the texture cache.
        void unload() override;

    private:
        SDL_Renderer& sdlRenderer_;
        std::unordered_map<std::string, std::shared_ptr<Texture>> textureCache_;
    };
}

#endif
