#include <iostream>

#include <SDL.h>

#include "src/core/Game.h"
#include "src/core/GameObject.h"
#include "src/core/Level.h"
#include "src/game/Player.h"
#include "src/utilities/Timer.h"

GameObject* createPlayer() 
{
	return new Player("res/steve.png");
}

int main(int argc, char* argv[])
{
	const int SCREEN_FPS = 60;
	const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

	Timer fpsTimer;
	Timer frameCapTimer;

	int countedFrames = 0;

	Game& game = Game::getInstance();
	game.registerObjectFactory("player", &createPlayer);

	if (!game.init("Butt Dragons", 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP))
		return -1;

	game.loadLevel("res/testmap.xml");

	fpsTimer.start();

	while (game.isRunning()) 
	{
		frameCapTimer.start();

		float averageFps = countedFrames / (fpsTimer.getTicks() / 1000.f);
		if (averageFps > 2000000)
			averageFps = 0;		

		game.handleEvents();
		game.update();
		game.render();

		countedFrames++;

		int frameTicks = frameCapTimer.getTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME)		
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);		
	}

	game.shutDown();

	return 0;
}