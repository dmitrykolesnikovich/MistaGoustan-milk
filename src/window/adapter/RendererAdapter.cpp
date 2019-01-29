#include <iostream>

#include "SDL_hints.h"
#include "SDL_render.h"

#include "RendererAdapter.h"

milk::adapter::RendererAdapter::RendererAdapter()
        : resolutionWidth_(0),
          resolutionHeight_(0)
{
}

bool milk::adapter::RendererAdapter::init(SDL_Window* sdlWindow,
                                          unsigned int resolutionWidth,
                                          unsigned int resolutionHeight)
{
    resolutionWidth_ = resolutionWidth;
    resolutionHeight_ = resolutionHeight;

    sdlRenderer_ = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (sdlRenderer_ == nullptr)
    {
        std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    SDL_RenderSetLogicalSize(sdlRenderer_, resolutionWidth, resolutionHeight);
    SDL_SetRenderDrawColor(sdlRenderer_, 0x00, 0x00, 0x00, 0xff);
    SDL_SetRenderDrawBlendMode(sdlRenderer_, SDL_BLENDMODE_BLEND);

    return true;
}

void milk::adapter::RendererAdapter::clear()
{
    SDL_SetRenderDrawColor(sdlRenderer_, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(sdlRenderer_);
}

void milk::adapter::RendererAdapter::present()
{
    SDL_RenderPresent(sdlRenderer_);
}

milk::Resolution milk::adapter::RendererAdapter::resolution() const
{
    Resolution res = {};
    res.width = resolutionWidth_;
    res.height = resolutionHeight_;

    return res;
}

void milk::adapter::RendererAdapter::free()
{
    SDL_DestroyRenderer(sdlRenderer_);
}

SDL_Renderer* milk::adapter::RendererAdapter::sdlRenderer() const
{
    return sdlRenderer_;
}
