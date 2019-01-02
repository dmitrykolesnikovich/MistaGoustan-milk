#include "core/Game.h"

int main(int argc, char* argv[])
{
	GameRunParameters runParams;
	runParams.title = "Butt Dragons";
	runParams.width = 1280;
	runParams.height = 720;
	runParams.virtualWidth = 640;
	runParams.virtualHeight = 360;
	runParams.fullscreen = false;
	runParams.resourceRootDir = "res";
	runParams.entryScene = "main_scene.json";

	Game game(runParams);

	return game.run();
}