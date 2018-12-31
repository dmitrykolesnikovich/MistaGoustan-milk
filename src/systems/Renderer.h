#ifndef _RENDER_SYSTEM_
#define _RENDER_SYSTEM_

#include <unordered_map>

class Actor;
class Camera;
class GameEvent;
class ResourceManager;
class Scene;
class Sprite;
class Tilemap;

struct SDL_Renderer;

class Renderer
{
public:
	Renderer(SDL_Renderer* renderer, ResourceManager& resourceManager);

	void onActorAdded(Actor& actor);
	void onActorDestroyed(Actor& actor);

	void handleEvent(GameEvent& gameEvent);

	void render(Scene& scene);

private:
	SDL_Renderer* sdlRenderer_;
	ResourceManager& resourceManager_;

	std::unordered_map<int, Sprite*> spritesByActorId_;

	void renderTilemap(const Tilemap& tilemap, const Camera& camera);
	void renderActors(const Camera& camera);
};

#endif
