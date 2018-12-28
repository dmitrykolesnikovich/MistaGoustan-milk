#pragma once

#include "SDL.h"

static class Input 
{
public:
	Input();

	static bool getKey(SDL_Keycode keycode);
	static bool getKeyPressed(SDL_Keycode keycode, bool* lastState);
	static bool getKeyReleased(SDL_Keycode keycode, bool* lastState);

	static void initialize();
	static void updateKeyboardState();

private:
	static const Uint8* currentKeyboardState_;
};