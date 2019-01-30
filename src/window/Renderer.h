#ifndef MILK_RENDERER_H
#define MILK_RENDERER_H

namespace milk
{
    class Rectangle;
    class Texture;

    struct Resolution
    {
        int width, height;
    };

    // The renderer is used for drawing textures to the screen.
    class Renderer
    {
    public:
        // Clear the renderer to black.
        virtual void clear() = 0;

        // Draw the texture.
        virtual void draw(Texture& texture,
                          Rectangle& sourceRectangle,
                          Rectangle& destinationRectangle,
                          int flipFlags) = 0;

        // Draw the contents of the renderer to the window.
        virtual void present() = 0;

        // Get the game resolution.
        virtual Resolution resolution() const = 0;
    };
}

#endif
