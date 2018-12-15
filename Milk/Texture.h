#pragma once

struct SDL_Texture;

class Texture
{
public:
	Texture(SDL_Texture* sdlTexture, int width, int height);
	~Texture();

	SDL_Texture* get() const;
	int getWidth() const;
	int getHeight() const;

private:
	SDL_Texture* _sdlTexture;

	int _width;
	int _height;
};
