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

TEST_F(SpriteTests, Load_GivenSourceRectNotSet_DefaultsFromTextureSize) {
    // Arrange
    milk::Actor actor{1, "steve", {0, 0}};

    auto pTexture = std::make_shared<milk::Texture>(nullptr, 50, 50);

    MTextureLoader textureLoader{"rootDir"};

    EXPECT_CALL(textureLoader, load("texturename"))
            .WillOnce(Return(pTexture));

    milk::Sprite sprite{actor, "texturename"};

    // Act
    sprite.load(textureLoader);

    // Assert
    auto sourceRect = sprite.sourceRect();

    ASSERT_EQ(0, sourceRect.x);
    ASSERT_EQ(0, sourceRect.y);
    ASSERT_EQ(50, sourceRect.w);
    ASSERT_EQ(50, sourceRect.h);
}

TEST_F(SpriteTests, Load_GivenSourceRectSet_DoesNotDefaultToTextureSize) {
    // Arrange
    milk::Actor actor{1, "steve", {0, 0}};

    auto pTexture = std::make_shared<milk::Texture>(nullptr, 500, 500);

    MTextureLoader textureLoader{"rootDir"};

    EXPECT_CALL(textureLoader, load("texturename"))
            .WillOnce(Return(pTexture));

    milk::Sprite sprite{actor, "texturename"};
    sprite.sourceRect(0, 0, 50, 50);

    // Act
    sprite.load(textureLoader);

    // Assert
    auto sourceRect = sprite.sourceRect();

    ASSERT_EQ(0, sourceRect.x);
    ASSERT_EQ(0, sourceRect.y);
    ASSERT_EQ(50, sourceRect.w);
    ASSERT_EQ(50, sourceRect.h);
}

TEST_F(SpriteTests, DestinationRect_ReturnsCorrectRect) { // aka corRect, yfeel me?
    // Arrange
    milk::Actor actor{1, "steve", {70, 30}};

    milk::Sprite sprite{actor, "texturename"};
    sprite.sourceRect(0, 0, 50, 50);

    // Act
    auto destRect = sprite.destinationRect();

    // Assert
    ASSERT_EQ(70, destRect.x);
    ASSERT_EQ(30, destRect.y);
    ASSERT_EQ(50, destRect.w);
    ASSERT_EQ(50, destRect.h);
}

TEST_F(SpriteTests, DestinationRect_GivenSpriteOriginCentered_ReturnsCorrectRect) {
    // Arrange
    milk::Actor actor{1, "steve", {70, 30}};

    milk::Sprite sprite{actor, "texturename"};
    sprite.sourceRect(0, 0, 50, 50);
    sprite.center();

    // Act
    auto destRect = sprite.destinationRect();

    // Assert
    ASSERT_EQ(45, destRect.x);
    ASSERT_EQ(5, destRect.y);
    ASSERT_EQ(50, destRect.w);
    ASSERT_EQ(50, destRect.h);
}

TEST_F(SpriteTests, FlipX_FlipsX) {
    // Arrange
    milk::Actor actor{1, "steve", {70, 30}};

    milk::Sprite sprite{actor, "texturename"};

    // Act
    sprite.flipX();

    // Assert
    ASSERT_TRUE(sprite.flippedX());
}


TEST_F(SpriteTests, FlipY_FlipsY) {
    // Arrange
    milk::Actor actor{1, "steve", {70, 30}};

    milk::Sprite sprite{actor, "texturename"};

    // Act
    sprite.flipY();

    // Assert
    ASSERT_TRUE(sprite.flippedY());
}

#endif
