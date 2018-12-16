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

	Game game;
	Level* level = game.loadLevel("res/testmap.xml");
	level->createGameObject<Player>("steve.png");

	if (!game.init("Butt Dragons", 640, 480, SDL_WINDOW_SHOWN))
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