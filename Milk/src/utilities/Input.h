#pragma once

#include <SDL.h>

static class Input 
{
public:
	Input();

	static bool getKey(SDL_Scancode scancode);
	static bool getkeyDown(SDL_Scancode scancode);
	static bool getKeyUp(SDL_Scancode scancode);

	static void initialize();
	static void updateKeyboardState();

private:
	static const Uint8* currentKeyboardState_;
	static const Uint8* previousKeyboardState_;
};