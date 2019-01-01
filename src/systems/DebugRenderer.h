#ifndef _DEBUG_RENDERER_
#define _DEBUG_RENDERER_

#include <unordered_map>

class Actor;
class ActorEvent;
class BoxCollider;
class Scene;

struct SDL_Renderer;

class DebugRenderer
{
public:
	DebugRenderer(SDL_Renderer& renderer);

	void handleEvent(ActorEvent& gameEvent);

	void render(Scene& scene);

	bool show = true;

private:
	SDL_Renderer& sdlRenderer_;

	std::unordered_map<int, Actor*> actorsById_;

	void onActorSpawned(Actor& actor);
	void onActorDestroyed(Actor& actor);
};

#endif
