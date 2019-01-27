#ifndef MILK_SPRITE_H
#define MILK_SPRITE_H

#include <string>

#include "SDL.h"

#include "scene/ActorComponent.h"

#include "utilities/Alignment.h"
#include "utilities/AssetLoader.h"

namespace milk {
    class Texture;

    // All objects that are drawn to the screen do so via the Sprite component.
    class Sprite : public ActorComponent {
    public:
        static const ComponentType type;

        explicit Sprite(Actor& actor, const std::string& textureName);

        ~Sprite() override = default;

        // Load the sprite's texture.
        void load(AssetLoader<Texture>& textureLoader);

        // Get the sprites texture.
        std::shared_ptr<Texture> texture() const;

        // Center the sprite's origin.
        void center();

        // Set the sprite's source rectangle.
        void sourceRect(int x, int y, int width, int height);

        // Get the sprite's source rectangle.
        SDL_Rect sourceRect() const;

        // Get the sprite's destination rectangle.
        SDL_Rect destinationRect() const;

        // Flip the sprite horizontally.
        void flipX();

        // Returns true if the sprite is flipped horizontally.
        bool flippedX();

        // Flip the sprite vertically.
        void flipY();

        // Returns true if the sprite is flipped vertically.
        bool flippedY();

        // Returns the renderer flip states.
        SDL_RendererFlip rendererFlip() const;

    private:
        std::string textureName_;
        std::shared_ptr<Texture> texture_;

        SDL_Rect sourceRect_;

        Alignment alignment_;

        Uint8 flip_;
    };
}

#endif
