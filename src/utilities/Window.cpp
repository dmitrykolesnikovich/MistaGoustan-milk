#include "Window.h"

#include <iostream>

#include "SDL.h"

Window::Window()
	: Window::Window("Milk", 800, 600, false)
{	
}

Window::Window(const std::string& title, unsigned int width, unsigned int height, bool fullscreen)
	: Window::Window(title, width, height, width, height, false)
{
}

Window::Window(const std::string& title, unsigned int width, unsigned int height, unsigned int virtualWidth, unsigned int virtualHeight, bool fullscreen)
	: title_(title)
	, width_(width)
	, height_(height)
	, virtualWidth_(virtualWidth)
	, virtualHeight_(virtualHeight)
	, isFullscreen_(fullscreen)
	, sdlWindow_(nullptr)
	, sdlRenderer_(nullptr)
{
}

Window::~Window()
{
	freeSDLResources();
}

bool Window::initSDLRenderWindow()
{
	SDL_DisplayMode currentDisplayMode;
	SDL_GetCurrentDisplayMode(0, &currentDisplayMode);

	int windowXPosition = (currentDisplayMode.w / 2) - (width_ / 2);
	int windowYPosition = (currentDisplayMode.h / 2) - (height_ / 2);

	int flags = SDL_WINDOW_SHOWN;

	if (isFullscreen_)
		flags |= SDL_WINDOW_FULLSCREEN;
;
	sdlWindow_ = SDL_CreateWindow(title_.c_str(), windowXPosition, windowYPosition, width_, height_, flags);

	if (sdlWindow_ == nullptr)
	{
		std::cout << "Error creating window: " << SDL_GetError() << std::endl;
		return false;
	}

	sdlRenderer_ = SDL_CreateRenderer(sdlWindow_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (sdlRenderer_ == nullptr)
	{
		SDL_DestroyWindow(sdlWindow_);
		std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	SDL_RenderSetLogicalSize(sdlRenderer_, virtualWidth_, virtualHeight_);
	SDL_SetRenderDrawColor(sdlRenderer_, 0x00, 0x00, 0x00, 0xff);

	return true;
}

unsigned int Window::width() const
{
	return width_;
}

unsigned int Window::height() const
{
	return height_;
}

void Window::size(unsigned int width, unsigned int height)
{
	width_ = width;
	height_ = height;
}

void Window::virtualSize(unsigned int virtualWidth, unsigned int virtualHeight)
{
	virtualWidth_ = virtualWidth;
	virtualHeight_ = virtualHeight;
}

bool Window::fullscreen() const
{
	return isFullscreen_;
}

void Window::toggleFullscreen()
{
	isFullscreen_ = !isFullscreen_;

	if (!isFullscreen_) 
	{
		const int WINDOWED = 0;
		SDL_SetWindowFullscreen(sdlWindow_, WINDOWED);
		SDL_SetWindowSize(sdlWindow_, width_, height_);
	}
	else
	{
		int displayIndex = SDL_GetWindowDisplayIndex(sdlWindow_);

		SDL_Rect displayBounds;
		SDL_GetDisplayBounds(displayIndex, &displayBounds);

		nativeWidth_ = displayBounds.w;
		nativeHeight_ = displayBounds.h;

		SDL_SetWindowSize(sdlWindow_, nativeWidth_, nativeHeight_);
		SDL_SetWindowFullscreen(sdlWindow_, SDL_WINDOW_FULLSCREEN);
	}
}

SDL_Window* Window::sdlWindow() const
{
	SDL_assert(sdlRenderer_ != nullptr);
	return sdlWindow_;
}

SDL_Renderer* Window::sdlRenderer() const
{
	SDL_assert(sdlRenderer_ != nullptr);
	return sdlRenderer_;
}

void Window::freeSDLResources()
{
	SDL_DestroyRenderer(sdlRenderer_);
	SDL_DestroyWindow(sdlWindow_);
}
