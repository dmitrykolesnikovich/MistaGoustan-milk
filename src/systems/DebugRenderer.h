#ifndef _DEBUG_RENDERER_
#define _DEBUG_RENDERER_

#include <unordered_map>

class Actor;
class BoxCollider;
class Scene;

struct SDL_Renderer;

class DebugRenderer
{
public:
	DebugRenderer(SDL_Renderer* renderer);

	void onActorAdded(Actor& actor);
	void onActorDestroyed(Actor& actor);

	void render(Scene& scene);

	bool show = true;

private:
	SDL_Renderer* sdlRenderer_;

	std::unordered_map<int, Actor*> actorsById_;
};

#endif
