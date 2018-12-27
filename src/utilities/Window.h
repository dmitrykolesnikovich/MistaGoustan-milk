#ifndef _WINDOW_
#define _WINDOW_

struct SDL_Window;
struct SDL_Renderer;

class Window
{
public:
	Window(SDL_Window& window, SDL_Renderer& renderer);
	~Window();

	unsigned int getWidth() const;
	unsigned int getHeight() const;

	bool isFullscreen() const;
	void toggleFullscreen();

private:
	unsigned int width_;
	unsigned int height_;
	unsigned int virtualWidth_;
	unsigned int virtualHeight_;

	bool isFullscreen_;

	SDL_Window& sdlWindow_;
	SDL_Renderer& sdlRenderer_;
};

#endif
