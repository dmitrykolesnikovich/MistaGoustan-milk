#ifndef MILK_GRAPHICS_H
#define MILK_GRAPHICS_H

#include <unordered_map>

#include "TextureLoader.h"

struct SDL_Renderer;

namespace milk {
    class Actor;

    class Camera;

    class GameEvent;

    class ResourceManager;

    class Scene;

    class Sprite;

    class Texture;

    struct Tilemap;

    class Graphics {
    public:
        Graphics(SDL_Renderer& renderer, const std::string& rootDir);

        void handleEvent(GameEvent& gameEvent);

        void render(Scene& scene);

    private:
        TextureLoader textureLoader;

        SDL_Renderer& sdlRenderer_;

        std::unordered_map<int, Sprite*> spritesByActorId_;

        void onActorSpawned(Actor& actor);

        void onActorDestroyed(Actor& actor);

        void renderTilemap(const Tilemap& tilemap, const Camera& camera);

        void renderActors(const Camera& camera);
    };
}

#endif
