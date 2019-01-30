#ifndef MILK_ASSET_LOADER_H
#define MILK_ASSET_LOADER_H

#include <memory>
#include <string>
#include <utility>

namespace milk
{
    // An asset cache does a bit more than it's name implies. It actually LOADS and caches assets.
    template<class TAsset>
    class AssetCache
    {
    public:
        explicit AssetCache(std::string rootDir)
                : rootDir_(std::move(rootDir))
        {
        }

        virtual ~AssetCache() = default;

        // Load the asset.
        virtual std::shared_ptr<TAsset> load(const std::string& assetName) = 0;

        virtual void invalidate() = 0;

    protected:
        const std::string rootDir_;

        std::string getPath(const std::string& assetName)
        {
            return rootDir_ + "/" + assetName;
        }
    };
}

#endif
