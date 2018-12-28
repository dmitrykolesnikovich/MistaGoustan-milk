#ifndef _RENDER_SYSTEM_
#define _RENDER_SYSTEM_

#include <unordered_map>

class Actor;
class ResourceManager;
class Sprite;
struct Tilemap;

struct SDL_Renderer;

class Renderer
{
public:
	Renderer(SDL_Renderer* renderer, ResourceManager& resourceManager);

	void onActorAdded(Actor& actor);
	void onActorDestroyed(Actor& actor);
	void onActorModified(Actor& actor);

	void render(Tilemap& tilemap);

private:
	SDL_Renderer* sdlRenderer_;
	ResourceManager& resourceManager_;

	std::unordered_map<int, Sprite*> spritesByActorId_;
};

#endif
