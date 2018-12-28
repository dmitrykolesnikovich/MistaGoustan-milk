#include "Texture.h"

#include"SDL.h"

Texture::Texture(SDL_Texture* sdlTexture, int width, int height)
	: sdlTexture_(sdlTexture)
	, width_(width)
	, height_(height)
{
}

Texture::~Texture()
{
	SDL_DestroyTexture(sdlTexture_);
}

SDL_Texture* Texture::get() const
{
	return sdlTexture_;
}

int Texture::width() const
{
	return width_;
}

int Texture::height() const
{
	return height_;
}
