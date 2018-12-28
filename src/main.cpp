#include <iostream>

#include <SDL.h>

#include "core/Game.h"
#include "utilities/Timer.h"

#include "core\Actor.h"
#include "core\Scene.h"
#include "components\Sprite.h"

int main(int argc, char* argv[])
{
	const int SCREEN_FPS = 60;
	const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

	Timer fpsTimer;
	Timer frameCapTimer;

	int countedFrames = 0;

	Game& game = Game::getInstance();

	if (!game.init("Butt Dragons", 640, 480, false))
		return -1;

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