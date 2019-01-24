#ifndef _WINDOW_H
#define _WINDOW_H

#include <string>

struct SDL_Window;
struct SDL_Renderer;

class Window {
public:
    Window();

    Window(const std::string& title, unsigned int width, unsigned int height, bool fullscreen);

    Window(const std::string& title, unsigned int width, unsigned int height, unsigned int virtualWidth,
           unsigned int virtualHeight, bool fullscreen);

    ~Window();

    // Initialize the SDL_Window and SDL_Renderer.
    bool init();

    // Clear the renderer to black.
    void clear();

    // Draw the contents of the renderer to the window.
    void present();

    // Get width of window.
    unsigned int width() const;

    // Get height of window.
    unsigned int height() const;

    // Get vritual width of window.
    unsigned int virtualWidth() const;

    // Get virtual height of window.
    unsigned int virtualHeight() const;

    // Set size of window.
    void size(unsigned int width, unsigned int height);

    // Set the virtual size of window.
    void virtualSize(unsigned int virtualWidth, unsigned int virtualHeight);

    // Returns true if window is in fullscreen mode.
    bool fullscreen() const;

    // Toggles fullscreen mode.
    void toggleFullscreen();

    // Get SDL_Window.
    SDL_Window* sdlWindow() const;

    // Get SDL_Renderer.
    SDL_Renderer* sdlRenderer() const;

    // Free all resources.
    void freeSDLResources();

private:
    std::string title_;

    unsigned int width_;
    unsigned int height_;

    unsigned int nativeWidth_;
    unsigned int nativeHeight_;

    unsigned int virtualWidth_;
    unsigned int virtualHeight_;

    bool isFullscreen_;

    SDL_Window* sdlWindow_;
    SDL_Renderer* sdlRenderer_;
};

#endif
