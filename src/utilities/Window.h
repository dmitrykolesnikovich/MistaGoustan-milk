#ifndef _WINDOW_
#define _WINDOW_

#include <string>

struct SDL_Window;
struct SDL_Renderer;

class Window
{
public:
	Window();
	Window(const std::string& title, unsigned int width, unsigned int height, bool fullscreen);
	~Window();

	// Initialize the SDL_Window and SDL_Renderer.
	bool initSDLRenderWindow();

	// Get width of window.
	unsigned int width() const;

	// Get height of window.
	unsigned int height() const;

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
	unsigned int virtualWidth_;
	unsigned int virtualHeight_;

	bool isFullscreen_;

	SDL_Window* sdlWindow_;
	SDL_Renderer* sdlRenderer_;
};

#endif
