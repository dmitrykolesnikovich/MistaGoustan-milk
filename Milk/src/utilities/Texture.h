#ifndef _TEXTURE_
#define _TEXTURE_

struct SDL_Texture;

class Texture
{
public:
	Texture(SDL_Texture* sdlTexture, int width, int height);
	~Texture();

	// Get the raw SDL_Texture.
	SDL_Texture* get() const;

	// Get texture width.
	int getWidth() const;

	// Get texture height.
	int getHeight() const;

private:
	SDL_Texture* _sdlTexture;

	int _width;
	int _height;
};

#endif
