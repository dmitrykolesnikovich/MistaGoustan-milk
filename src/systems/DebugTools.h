#ifndef _DEBUG_RENDERER_
#define _DEBUG_RENDERER_

#include <unordered_map>

class Actor;
class GameEvent;
class BoxCollider;
class Scene;

struct SDL_Renderer;

class DebugTools
{
public:
	explicit DebugTools(SDL_Renderer& renderer);

	void handleEvent(GameEvent& gameEvent);

	void render(Scene& scene);

	bool show = false;

private:
	SDL_Renderer& sdlRenderer_;

	std::unordered_map<int, Actor*> actorsById_;

	void onActorSpawned(Actor& actor);
	void onActorDestroyed(Actor& actor);
};

#endif
