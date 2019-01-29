#ifndef MILK_TEXTURE_H
#define MILK_TEXTURE_H

struct SDL_Texture;

namespace milk
{
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
}

#endif
