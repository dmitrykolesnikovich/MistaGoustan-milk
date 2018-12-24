#include "Input.h"
#include <iostream>

const Uint8* Input::currentKeyboardState_ = nullptr;

Input::Input()
{
}

bool Input::getKey(SDL_Keycode keycode)
{
	return currentKeyboardState_[SDL_GetScancodeFromKey(keycode)];
}

bool Input::getKeyPressed(SDL_Keycode keycode, bool* lastState)
{
	bool justPressed = getKey(keycode) && !*lastState;
	*lastState = getKey(keycode);

	return justPressed;
}

bool Input::getKeyReleased(SDL_Keycode keycode, bool* lastState)
{
	bool justReleased = !getKey(keycode) && *lastState;
	*lastState = getKey(keycode);

	return justReleased;
}

void Input::initialize()
{
	currentKeyboardState_ = SDL_GetKeyboardState(0);
}

void Input::updateKeyboardState()
{
	currentKeyboardState_ = SDL_GetKeyboardState(NULL);
}
