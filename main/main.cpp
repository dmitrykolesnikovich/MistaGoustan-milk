#include "game/Game.h"

int main(int argc, char* argv[])
{
	milk::Game game("res/config.lua");

	return game.run();
}