#ifndef _RENDER_SYSTEM_
#define _RENDER_SYSTEM_

#include <unordered_map>

class Actor;
class Camera;
class ActorEvent;
class ResourceManager;
class Scene;
class Sprite;

struct SDL_Renderer;
struct Tilemap;

class Renderer
{
public:
	Renderer(SDL_Renderer& renderer, ResourceManager& resourceManager);

	void handleEvent(ActorEvent& gameEvent);

	void render(Scene& scene);

private:
	SDL_Renderer& sdlRenderer_;
	ResourceManager& resourceManager_;

	std::unordered_map<int, Sprite*> spritesByActorId_;

	void onActorSpawned(Actor& actor);
	void onActorDestroyed(Actor& actor);

	void renderTilemap(const Tilemap& tilemap, const Camera& camera);
	void renderActors(const Camera& camera);
};

#endif
