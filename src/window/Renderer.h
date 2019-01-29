#ifndef MILK_RENDERER_H
#define MILK_RENDERER_H

namespace milk
{
    struct Resolution
    {
        int width, height;
    };

    class Renderer
    {
    public:
        // Clear the renderer to black.
        virtual void clear() = 0;

        // Draw the contents of the renderer to the window.
        virtual void present() = 0;

        virtual Resolution resolution() const = 0;
    };
}

#endif
