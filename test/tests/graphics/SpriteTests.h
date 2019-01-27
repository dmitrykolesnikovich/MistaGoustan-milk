#ifndef MILK_SPRITE_TESTS_H
#define MILK_SPRITE_TESTS_H

#include <memory>

// google test
#include "gtest/gtest.h"

using ::testing::Return;

#include "mocks/graphics/MTextureLoader.h"

#include "graphics/Sprite.h"
#include "graphics/Texture.h"
#include "scene/Actor.h"

class SpriteTests : public ::testing::Test {};

TEST_F(SpriteTests, Ctor_Constructs) {
    // Arrange
    milk::Actor actor{1, "steve", {0, 0}};

    // Act & Assert
    ASSERT_NO_THROW(milk::Sprite(actor, "texturename"));
}

TEST_F(SpriteTests, Load_LoadsTexture) {
    // Arrange
    milk::Actor actor{1, "steve", {0, 0}};

    auto pTexture = std::make_shared<milk::Texture>(nullptr, 0, 0);

    MTextureLoader textureLoader{"rootDir"};

    EXPECT_CALL(textureLoader, load("texturename"))
        .WillOnce(Return(pTexture));

    milk::Sprite sprite{actor, "texturename"};

    // Act
    sprite.load(textureLoader);

    // Assert
    ASSERT_EQ(sprite.texture().get(), pTexture.get());
}

#endif
