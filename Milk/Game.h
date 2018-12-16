#pragma once

struct SDL_Window;
struct SDL_Renderer;

class GameObject;
class Level;

class Game
{
public:
	Game();
	~Game();

	bool init(const char* title, unsigned int width, unsigned int height, int flags);

	void handleEvents();
	void update();
	void render();

	bool isRunning() const;

	SDL_Renderer& getRenderer();

	void loadLevel(Level* level);
	Level* loadLevel(const char* filename);

	void shutDown();

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	Level* _currentLevel;
	Level* _nextLevel;

	bool _isRunning;
};
