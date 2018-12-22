#pragma once

#include "../core/System.h"

struct SDL_Renderer;

class Renderer : public System
{
public:
	Renderer(SDL_Renderer& renderer);

	virtual void update(Scene& scene) override;

private:
	SDL_Renderer& _renderer;
};