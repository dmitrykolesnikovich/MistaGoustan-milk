#ifndef _GAME_
#define _GAME_

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

struct SDL_Window;
struct SDL_Renderer;

class GameObject;
class Level;

class Game
{
public:
	~Game();

	// Returns a reference to the single instance of Game.
	static Game& getInstance();

	// Initializes game systems, window and renderer.
	bool init(const char* title, unsigned int width, unsigned int height, int flags);

	// Handles input events.
	void handleEvents();

	// Updates the current level.
	void update();

	// Renders the current level.
	void render();

	// Returns true if game is running.
	bool isRunning() const;

	// Returns a reference to the games renderer.
	SDL_Renderer& getRenderer();

	// Loads an XML based level from resource file.
	Level* loadLevel(const char* filename);

	// Shuts down game systems and frees resources.
	void shutDown();

	void registerObjectFactory(const std::string& name, std::function<GameObject*(void)> factoryMethod);

	GameObject* createFromFactory(const std::string& name);

private:
	Game() {}

	SDL_Window* _window;
	SDL_Renderer* _renderer;

	Level* _currentLevel;
	Level* _nextLevel;

	std::unordered_map<std::string, std::function<GameObject*(void)>> _gameObjectFactories;

	bool _isRunning;
};

#endif
