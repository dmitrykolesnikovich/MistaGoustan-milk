#ifndef MILK_WINDOW_H
#define MILK_WINDOW_H

#include <string>

namespace milk
{
    class Renderer;

    class Window
    {
    public:
        // Get width of window.
        virtual unsigned int width() const = 0;

        // Get height of window.
        virtual unsigned int height() const = 0;

        // Returns true if window is in fullscreen mode.
        virtual bool fullscreen() const = 0;

        // Toggles fullscreen mode.
        virtual void toggleFullscreen() = 0;

        // Get window's renderer.
        virtual Renderer& renderer() const = 0;
    };
}

#endif
