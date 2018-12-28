#include "core/Game.h"

int main(int argc, char* argv[])
{
	GameRunParameters runParams;
	runParams.title = "Butt Dragons";
	runParams.width = 640;
	runParams.height = 360;
	runParams.fullscreen = false;
	runParams.resourceRootDir = "res";
	runParams.entryScene = "res/testmap.xml";

	Game game(runParams);

	return game.run();
}