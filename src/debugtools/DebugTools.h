#ifndef MILK_DEBUG_TOOLS_H
#define MILK_DEBUG_TOOLS_H

#include <unordered_map>

struct SDL_Renderer;

namespace milk
{
    class Actor;
    class GameEvent;
    class BoxCollider;
    class Scene;

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
}

#endif
