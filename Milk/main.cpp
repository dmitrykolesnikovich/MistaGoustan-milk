#include <iostream>

#include <SDL.h>

#include "src/core/Game.h"
#include "src/core/GameObject.h"
#include "src/core/Level.h"
#include "src/game/Player.h"

GameObject* createPlayer() 
{
	return new Player("res/steve.png");
}

int main(int argc, char* argv[])
{
	const int fps = 60;
	const int delay = 1000.0f / fps;

	Uint32 frameStart;
	Uint32 frameTime;

	Game& game = Game::getInstance();
	game.registerObjectFactory("player", &createPlayer);

	if (!game.init("Butt Dragons", 640, 480, SDL_WINDOW_SHOWN))
		return -1;

	game.loadLevel("res/testmap.xml");

	while (game.isRunning()) 
	{
		frameStart = SDL_GetTicks();

		game.handleEvents();
		game.update();
		game.render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameTime < delay)
			SDL_Delay((int)delay - frameTime);
	}

	game.shutDown();

	return 0;
}