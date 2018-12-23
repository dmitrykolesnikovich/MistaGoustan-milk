#ifndef _RENDER_SYSTEM_
#define _RENDER_SYSTEM_

#include <unordered_map>

#include "../core/System.h"

class ResourceManager;
class Sprite;

struct SDL_Renderer;

class Renderer : public System
{
public:
	Renderer(SDL_Renderer& renderer, ResourceManager& resourceManager);

	virtual void onActorAdded(Actor& actor) override;
	virtual void onActorDestroyed(Actor& actor) override;
	virtual void onActorModified(Actor& actor) override;

	virtual void update(Scene& scene) override;

private:
	SDL_Renderer& sdlRenderer_;
	ResourceManager& resourceManager_;

	std::unordered_map<int, Sprite*> spritesByActorId_;
};

#endif
