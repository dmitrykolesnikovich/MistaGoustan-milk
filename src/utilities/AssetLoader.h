#ifndef MILK_ASSET_LOADER_H
#define MILK_ASSET_LOADER_H

#include <memory>
#include <string>
#include <utility>

namespace milk {
    template<class TAsset>
    class AssetLoader {
    public:
        explicit AssetLoader(std::string rootDir)
            : rootDir_(std::move(rootDir)) {
        }

        virtual ~AssetLoader() = default;

        virtual std::shared_ptr<TAsset> load(const std::string& assetName) = 0;

        virtual void unload() = 0;

    protected:
        const std::string rootDir_;

        std::string getPath(const std::string& assetName) {
            return rootDir_ + "/" + assetName;
        }
    };
}

#endif
