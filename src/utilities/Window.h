#ifndef _WINDOW_
#define _WINDOW_

#include <string>

struct SDL_Window;
struct SDL_Renderer;

class Window
{
public:
	Window(const std::string& title, unsigned int width, unsigned int height, bool fullscreen);
	~Window();

	bool init();

	unsigned int getWidth() const;
	unsigned int getHeight() const;

	void setSize(unsigned int width, unsigned int height);
	void setVirtualSize(unsigned int virtualWidth, unsigned int virtualHeight);

	bool isFullscreen() const;
	void toggleFullscreen();

	SDL_Window& getSdlWindow() const;
	SDL_Renderer* getSdlRenderer() const;

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
