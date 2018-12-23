#ifndef _GAME_
#define _GAME_

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <memory>

#include "Scene.h"

#include "../systems/Renderer.h"
#include "../utilities/ResourceManager.h"

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
	bool init(const std::string& title, unsigned int width, unsigned int height, int flags);

	// Handles user input events.
	void handleEvents();

	// Updates the games systems.
	void update();

	// Renders the games current scene.
	void render();

	// Returns true if game is running.
	bool isRunning() const;

	// Returns a reference to the games renderer.
	SDL_Renderer& getRenderer() const;

	// Returns a reference to the games resource manager.
	ResourceManager& getResourceManager() const;

	// Shuts down game systems and frees resources.
	void shutDown();

	void onActorAdded(Actor& actor);

private:
	Game() {}

	SDL_Window* _window;
	SDL_Renderer* _renderer;

	std::unique_ptr<ResourceManager> _resourceManager;
	std::unique_ptr<Renderer> _renderSystem;

	std::unique_ptr<Scene> _currentScene;

	bool _isRunning;
};

#endif
