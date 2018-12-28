#include "Window.h"

#include <iostream>
#include "SDL.h"

Window::Window(const std::string& title, unsigned int width, unsigned int height, bool fullscreen)
{
	title_ = title;
	width_ = width;
	height_ = height;
	virtualWidth_ = width;
	virtualHeight_ = height;
	isFullscreen_ = fullscreen;

	sdlWindow_ = nullptr;
	sdlRenderer_ = nullptr;
}

Window::~Window()
{
	SDL_DestroyRenderer(sdlRenderer_);
	SDL_DestroyWindow(sdlWindow_);
}

bool Window::init()
{
	SDL_DisplayMode currentDisplayMode;
	SDL_GetCurrentDisplayMode(0, &currentDisplayMode);

	int windowXPosition = (currentDisplayMode.w / 2) - (width_ / 2);
	int windowYPosition = (currentDisplayMode.h / 2) - (height_ / 2);

	int flags = SDL_WINDOW_SHOWN;

	if (isFullscreen_)
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
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

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
	SDL_RenderSetLogicalSize(sdlRenderer_, virtualWidth_, virtualHeight_);
	SDL_SetRenderDrawColor(sdlRenderer_, 0x00, 0x00, 0x00, 0xff);

	return true;
}

unsigned int Window::getWidth() const
{
	return width_;
}

unsigned int Window::getHeight() const
{
	return height_;
}

void Window::setSize(unsigned int width, unsigned int height)
{
	width_ = width;
	height_ = height;
}

void Window::setVirtualSize(unsigned int virtualWidth, unsigned int virtualHeight)
{
	virtualWidth_ = virtualWidth;
	virtualHeight_ = virtualHeight;
}

bool Window::isFullscreen() const
{
	return isFullscreen_;
}

void Window::toggleFullscreen()
{
	isFullscreen_ = !isFullscreen_;
}

SDL_Window& Window::getSdlWindow() const
{
	SDL_assert(sdlWindow_ != nullptr);
	return *sdlWindow_;
}

SDL_Renderer* Window::getSdlRenderer() const
{
	SDL_assert(sdlRenderer_ != nullptr);
	return sdlRenderer_;
}
