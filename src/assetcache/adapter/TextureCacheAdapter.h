#ifndef MILK_TEXTURE_LOADER_H
#define MILK_TEXTURE_LOADER_H

#include <string>
#include <unordered_map>

#include "assetcache/AssetCache.h"

struct SDL_Renderer;

namespace milk
{
    class Texture;

    namespace adapter
    {
        class TextureCacheAdapter : public AssetCache<Texture>
        {
        public:
            TextureCacheAdapter(SDL_Renderer& sdlRenderer, const std::string& rootDir);

            // Initialize the texture cache.
            bool init();

            // Loads the texture/fetches it from cache and returns it.
            std::shared_ptr<Texture> load(const std::string& textureName) override;

            // Invalidates the texture cache.
            void freeUnreferencedAssets() override;

            // Complete shut down of texture cache and free all texture resources.
            void free();

        private:
            SDL_Renderer& sdlRenderer_;
            std::unordered_map<std::string, std::shared_ptr<Texture>> textureCache_;
        };
    }
}

#endif
