#include "Texture.h"

#include <SDL.h>

Texture::Texture(SDL_Texture* sdlTexture, int width, int height)
	: _sdlTexture(sdlTexture), _width(width), _height(height)
{
}

Texture::~Texture()
{
	SDL_DestroyTexture(_sdlTexture);
}

SDL_Texture* Texture::get() const
{
	return _sdlTexture;
}

int Texture::getWidth() const
{
	return _width;
}

int Texture::getHeight() const
{
	return _height;
}
