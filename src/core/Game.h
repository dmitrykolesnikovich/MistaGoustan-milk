#ifndef _GAME_
#define _GAME_

#define MILK_SUCCESS 0
#define MILK_FAIL 1

#include <memory>
#include <string>
#include <unordered_map>

#include "Scene.h"
#include "SystemManager.h"

#include "../externals/sol.hpp"

#include "../utilities/ResourceManager.h"
#include "../utilities/SceneLoader.h"
#include "../utilities/Window.h"

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

	// Returns the games system manager.
	SystemManager& systemManager();

	// Loads an XML based scene.
	void loadScene(const std::string& name);

private:
	Window window_;

	SceneLoader sceneLoader_;
	ResourceManager resourceManager_;
	SystemManager systemManager_;

	sol::state luaState_;

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
