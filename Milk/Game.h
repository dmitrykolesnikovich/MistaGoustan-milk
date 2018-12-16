#ifndef _GAME_
#define _GAME_

#include <memory>

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

private:
	Game() {}

	SDL_Window* _window;
	SDL_Renderer* _renderer;

	std::unique_ptr<Level> _currentLevel;
	std::unique_ptr<Level> _nextLevel;

	bool _isRunning;
};

#endif
