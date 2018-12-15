#include <iostream>

#include <SDL.h>

#include "Game.h"
#include "GameObject.h"
#include "Level.h"
#include "Player.h"

int main(int argc, char* argv[])
{
	const int fps = 60;
	const int delay = 1000.0f / fps;

	Uint32 frameStart;
	Uint32 frameTime;

	Level* level = new Level();
	level->createGameObject<Player>("steve.png");

	Game game;
	game.loadLevel(level);

	if (!game.init("Butt Dragons", 640, 360, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP))
		return -1;

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