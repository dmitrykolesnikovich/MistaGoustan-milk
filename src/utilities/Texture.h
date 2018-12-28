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
	int width() const;

	// Get texture height.
	int height() const;

private:
	SDL_Texture* sdlTexture_;

	int width_;
	int height_;
};

#endif
