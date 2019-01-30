#ifndef MILK_GRAPHICS_H
#define MILK_GRAPHICS_H

#include <unordered_map>

struct SDL_Renderer;

namespace milk
{
    class Actor;
    class Camera;
    class GameEvent;
    class Renderer;
    class Scene;
    class Sprite;
    class Texture;

    template<class T>
    class AssetCache;

    struct Tilemap;

    // Graphics handles loading textures, and drawing scenes.
    class Graphics
    {
    public:
        // Graphics makes draw calls to the renderer, and loads necessary textures for rendering.
        Graphics(Renderer& renderer, AssetCache<Texture>& textureCache);

        // Graphics works on actor components, so it needs to be updated when they are spawned, destroyed, etc...
        void handleEvent(GameEvent& gameEvent);

        // Render the current scene and all of its components.
        // TODO: remove scene param. It is only used for tilemap rendering, and theres a better way handle it.
        void render(Scene& scene);

    private:
        Renderer& renderer_;
        AssetCache<Texture>& textureCache_;

        // We only store references to sprites in the graphics system.
        // Every frame, if the sprite also has an animator, we update the animator.
        std::unordered_map<int, Sprite*> spritesByActorId_;

        void onActorSpawned(Actor& actor);

        void onActorDestroyed(Actor& actor);

        void onSceneChanged();

        void renderTilemap(const Tilemap& tilemap, const Camera& camera);

        void renderActors(const Camera& camera);
    };
}

#endif
