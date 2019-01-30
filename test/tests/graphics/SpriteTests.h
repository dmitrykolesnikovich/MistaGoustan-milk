#ifndef MILK_SPRITE_TESTS_H
#define MILK_SPRITE_TESTS_H

#include <memory>

#include "gtest/gtest.h"

#include "mocks/graphics/MockTextureCache.h"

#include "graphics/Sprite.h"
#include "graphics/Texture.h"
#include "scene/Actor.h"

using ::testing::Return;

class SpriteTests : public ::testing::Test
{
};

TEST_F(SpriteTests, Ctor_Constructs)
{
    // Arrange
    milk::Actor actor{1, "steve", {0, 0}};

    // Act & Assert
    ASSERT_NO_THROW(milk::Sprite(actor, "texturename"));
}

TEST_F(SpriteTests, Load_LoadsTexture)
{
    // Arrange
    milk::Actor actor{1, "steve", {0, 0}};

    auto pTexture = std::make_shared<milk::Texture>(nullptr, 0, 0);

    MockTextureCache textureLoader{"rootDir"};

    EXPECT_CALL(textureLoader, load("texturename"))
            .WillOnce(Return(pTexture));

    milk::Sprite sprite{actor, "texturename"};

    // Act
    sprite.load(textureLoader);

    // Assert
    ASSERT_EQ(sprite.texture().get(), pTexture.get());
}

TEST_F(SpriteTests, Load_GivenSourceRectNotSet_DefaultsFromTextureSize)
{
    // Arrange
    milk::Actor actor{1, "steve", {0, 0}};

    auto pTexture = std::make_shared<milk::Texture>(nullptr, 50, 50);

    MockTextureCache textureLoader{"rootDir"};

    EXPECT_CALL(textureLoader, load("texturename"))
            .WillOnce(Return(pTexture));

    milk::Sprite sprite{actor, "texturename"};

    // Act
    sprite.load(textureLoader);

    // Assert
    auto sourceRect = sprite.sourceRect();

    ASSERT_EQ(0, sourceRect.x);
    ASSERT_EQ(0, sourceRect.y);
    ASSERT_EQ(50, sourceRect.width);
    ASSERT_EQ(50, sourceRect.height);
}

TEST_F(SpriteTests, Load_GivenSourceRectSet_DoesNotDefaultToTextureSize)
{
    // Arrange
    milk::Actor actor{1, "steve", {0, 0}};

    auto pTexture = std::make_shared<milk::Texture>(nullptr, 500, 500);

    MockTextureCache textureLoader{"rootDir"};

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
    ASSERT_EQ(50, sourceRect.width);
    ASSERT_EQ(50, sourceRect.height);
}

TEST_F(SpriteTests, DestinationRect_ReturnsCorRect)
{
    // Arrange
    milk::Actor actor{1, "steve", {70, 30}};

    milk::Sprite sprite{actor, "texturename"};
    sprite.sourceRect(0, 0, 50, 50);

    // Act
    auto destRect = sprite.destinationRect();

    // Assert
    ASSERT_EQ(70, destRect.x);
    ASSERT_EQ(30, destRect.y);
    ASSERT_EQ(50, destRect.width);
    ASSERT_EQ(50, destRect.height);
}

TEST_F(SpriteTests, DestinationRect_GivenSpriteOriginCentered_ReturnsCorRect)
{
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
    ASSERT_EQ(50, destRect.width);
    ASSERT_EQ(50, destRect.height);
}

TEST_F(SpriteTests, FlipX_FlipsX)
{
    // Arrange
    milk::Actor actor{1, "steve", {70, 30}};

    milk::Sprite sprite{actor, "texturename"};

    // Act
    sprite.flipX();

    // Assert
    ASSERT_TRUE(sprite.flippedX());
}


TEST_F(SpriteTests, FlipY_FlipsY)
{
    // Arrange
    milk::Actor actor{1, "steve", {70, 30}};

    milk::Sprite sprite{actor, "texturename"};

    // Act
    sprite.flipY();

    // Assert
    ASSERT_TRUE(sprite.flippedY());
}

TEST_F(SpriteTests, RendererFlip_ReturnsExpectedResult)
{
    // Arrange
    milk::Actor actor{1, "steve", {70, 30}};

    milk::Sprite sprite{actor, "texturename"};

    // Act & Assert
    ASSERT_EQ(SDL_FLIP_NONE, (sprite.rendererFlip() & SDL_FLIP_NONE));

    sprite.flipY();
    ASSERT_EQ(SDL_FLIP_VERTICAL, (sprite.rendererFlip() & SDL_FLIP_VERTICAL));

    sprite.flipY();
    sprite.flipX();
    ASSERT_EQ(SDL_FLIP_HORIZONTAL, (sprite.rendererFlip() & SDL_FLIP_HORIZONTAL));

    sprite.flipY();
    ASSERT_EQ((SDL_FLIP_HORIZONTAL & SDL_FLIP_VERTICAL),
              (sprite.rendererFlip() & (SDL_FLIP_HORIZONTAL & SDL_FLIP_VERTICAL)));
}

#endif
