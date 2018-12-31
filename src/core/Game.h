#ifndef _GAME_
#define _GAME_

#define MILK_SUCCESS 0
#define MILK_FAIL 1

#include <memory>
#include <string>
#include <unordered_map>

#include "Scene.h"

#include "../externals/sol.hpp"

#ifdef _DEBUG
#include "../systems/DebugRenderer.h"
#endif

#include "../systems/EventQueue.h"
#include "../systems/Logic.h"
#include "../systems/Renderer.h"
#include "../systems/Physics.h"

#include "../utilities/ResourceManager.h"
#include "../utilities/SceneLoader.h"
#include "../utilities/Window.h"

class Actor;

struct GameRunParameters 
{
	std::string title;
	unsigned int width;
	unsigned int height;
	unsigned int virtualWidth;
	unsigned int virtualHeight;
	bool fullscreen;
	std::string entryScene;
	std::string resourceRootDir;
};

class Game
{
public:
	Game();
	Game(const GameRunParameters& runParams);
	~Game() = default;

	// Initializes and runs the game
	// Returns MILK_SUCCESS on successful run
	// Returns MILK_FAIL on unsuccessful run
	int run();

	// Returns the game window.
	Window& window();

	// Returns the games resource manager.
	ResourceManager& resourceManager();

	// Loads an XML based scene.
	void loadScene(const std::string& name);

	// Called when an actor has been spawned in the current scene.
	void onActorSpawned(Actor& actor);

	// Called when an actor has been destroyed in the current scene.
	void onActorDestroyed(Actor& actor);

private:
	Window window_;

	SceneLoader sceneLoader_;
	ResourceManager resourceManager_;
	EventQueue eventQueue_;

	sol::state luaState_;

#ifdef _DEBUG
	std::unique_ptr<DebugRenderer> debugRenderer_;
#endif
	
	std::unique_ptr<Logic> logicSystem_;
	std::unique_ptr<Physics> physicsSystem_;
	std::unique_ptr<Renderer> renderSystem_;

	std::unique_ptr<Scene> currentScene_;
	std::string sceneToLoad_;

	bool isRunning_;

	bool initSDLSubsystems();
	bool initGameWindow();
	void initLua();
	void initGameSubsystems();
	void handleEvents();
	void update();
	void render();
	void shutDown();
};

#endif
