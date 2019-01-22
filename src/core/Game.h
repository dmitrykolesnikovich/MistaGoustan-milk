#ifndef _GAME_H
#define _GAME_H

#define MILK_SUCCESS 0
#define MILK_FAIL 1

#include <memory>
#include <string>
#include <unordered_map>

#include "Scene.h"

#include "externals/sol.hpp"

#include "systems/EventQueue.h"
#include "systems/SceneManager.h"

#include "utilities/ResourceManager.h"
#include "utilities/SceneLoader.h"
#include "utilities/Window.h"

#ifdef _DEBUG
class DebugRenderer;
#endif

class Logic;
class Physics;
class Renderer;

// TODO: Make configurable via lua script
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

// THE Game.
// As of right now, it's pretty much responsible for a lot of stuff.
// TODO: Give game a better description about it's responsibilities
class Game
{
public:
    Game();
	explicit Game(const GameRunParameters& runParams);

	~Game();

	// Initializes and runs the game
	// Returns MILK_SUCCESS on successful run
	// Returns MILK_FAIL on unsuccessful run
	int run();

	// Returns the game window.
	Window& window();

	// Returns the games resource manager.
	ResourceManager& resources();

	// Returns the games event queue.
	EventQueue& events();

	// Loads an JSON scene.
	void loadScene(const std::string& name);

private:
	Window window_;
	SceneLoader sceneLoader_; // TODO: Make sceneLoader a part of resources?
	ResourceManager resources_;
	SceneManager sceneManager_;

	sol::state luaState_;

	EventQueue events_;

#ifdef _DEBUG
	std::unique_ptr<DebugRenderer> debugTools_;
#endif

	std::unique_ptr<Logic> logic_;
	std::unique_ptr<Physics> physics_;
	std::unique_ptr<Renderer> graphics_;

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
