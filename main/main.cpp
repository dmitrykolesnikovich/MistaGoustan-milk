#include "core/Game.h"

int main(int argc, char* argv[])
{
	Game game("res/config.lua");

	return game.run();
}