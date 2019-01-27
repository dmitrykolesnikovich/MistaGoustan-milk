#ifndef MILK_MTEXTURE_LOADER_H
#define MILK_MTEXTURE_LOADER_H

// Google mock
#include "gmock/gmock.h"

#include "graphics/Texture.h"
#include "utilities/AssetLoader.h"

class MTextureLoader : public milk::AssetLoader<milk::Texture> {
public:
    explicit MTextureLoader(const std::string& rootDir)
        : AssetLoader(rootDir) {
    }
    MOCK_METHOD1(load, std::shared_ptr<milk::Texture>(const std::string&));
    MOCK_METHOD0(unload, void());
};

#endif
