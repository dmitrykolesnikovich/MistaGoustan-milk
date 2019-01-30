#ifndef MILK_GAME_H
#define MILK_GAME_H

// Exit codes
#define MILK_SUCCESS 0
#define MILK_FAIL 1

#include <memory>
#include <string>
#include <unordered_map>

#include "externals/sol.hpp"

namespace milk
{
#ifdef _DEBUG

    class DebugTools;

#endif

    class EventQueue;
    class Graphics;
    class Logic;
    class Physics;
    class ResourceManager;
    class SceneLoader;
    class SceneManager;
    class Window;

    namespace adapter
    {
        class TextureCache;
        class WindowAdapter;
    }

    // THE Game class.
    // Handles running the game, updating subsystems, managing scenes, handling input, etc..
    class Game
    {
    public:
        Game();

        explicit Game(const std::string& configFile);

        ~Game();

        // Initializes and runs the game
        // Returns MILK_SUCCESS on successful run
        // Returns MILK_FAIL on unsuccessful run
        int run();

        // Returns the game window.
        Window& window() const;

        // Returns the games resource manager.
        ResourceManager& resources() const;

        // Returns the games event queue.
        EventQueue& events() const;

        // Returns the games scene manager.
        SceneManager& sceneManager() const;

        // Loads an JSON scene.
        void loadScene(const std::string& name);

    private:
        std::string configFile_;

        // TODO: revisit.
        std::string assetRootDir_;

        std::unique_ptr<adapter::WindowAdapter> window_;
        std::unique_ptr<adapter::TextureCache> textureCache_;

        std::unique_ptr<SceneLoader> sceneLoader_;
        std::unique_ptr<ResourceManager> resources_;
        std::unique_ptr<SceneManager> sceneManager_;
        std::unique_ptr<EventQueue> events_;

        sol::state luaState_;

#ifdef _DEBUG
        std::unique_ptr<DebugTools> debugTools_;
#endif

        std::unique_ptr<Logic> logic_;
        std::unique_ptr<Physics> physics_;
        std::unique_ptr<Graphics> graphics_;

        bool isRunning_;

        void initLua();

        bool initFromConfig();

        bool initSDL();

        void initSystems();

        void handleEvents();

        void update();

        void render();

        void shutDown();
    };
}

#endif
