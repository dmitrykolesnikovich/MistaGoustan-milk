#ifndef _GAME_
#define _GAME_

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <memory>

#include "Scene.h"

#include "../externals/sol.hpp"
#include "../systems/Logic.h"
#include "../systems/Renderer.h"
#include "../systems/Physics.h"
#include "../utilities/ResourceManager.h"
#include "../utilities/Window.h"

class Actor;

struct SDL_Window;
struct SDL_Renderer;

class Game
{
public:
	~Game();

	// Returns a reference to the single instance of Game.
	// Should only be used at a high level (main.cpp), and passed as an argument to all dependents.
	static Game& getInstance();

	// Initializes game systems, window and renderer.
	bool init(const std::string& title, unsigned int width, unsigned int height, bool fullscreen);

	// Handles user input events.
	void handleEvents();

	// Updates the games systems.
	void update();

	// Renders the games current scene.
	void render();

	// Returns true if game is running.
	bool isRunning() const;

	// Shuts down game systems and frees resources.
	void shutDown();

	Window& getWindow() const;

	// Called when an actor has been spawned into the current scene.
	void onActorSpawned(Actor& actor);

	// Called when an actor has been destroyed in the current scene.
	void onActorDestroyed(Actor& actor);

private:
	Game() {}

	std::unique_ptr<Window> window_;

	std::unique_ptr<ResourceManager> resourceManager_;

	sol::state luaState_;

	std::unique_ptr<Logic> logicSystem_;
	std::unique_ptr<Physics> physicsSystem_;
	std::unique_ptr<Renderer> renderSystem_;

	std::unique_ptr<Scene> currentScene_;

	bool isRunning_;

	bool initSDL();
	bool initWindow(const std::string& title, unsigned int width, unsigned int height, bool fullscreen);
	bool initLua();
	bool initSystems();
};

#endif
