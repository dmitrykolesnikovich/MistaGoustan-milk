#include "Input.h"
#include <iostream>

const Uint8* Input::currentKeyboardState_ = nullptr;
const Uint8* Input::previousKeyboardState_ = nullptr;

Input::Input()
{
}

bool Input::getKey(SDL_Scancode scancode)
{
	return currentKeyboardState_[scancode];
}

bool Input::getkeyDown(SDL_Scancode scancode)
{
	return currentKeyboardState_[scancode] && !previousKeyboardState_[scancode];
}

bool Input::getKeyUp(SDL_Scancode scancode)
{
	return !currentKeyboardState_[scancode] && previousKeyboardState_[scancode];
}

void Input::initialize()
{
	currentKeyboardState_ = SDL_GetKeyboardState(0);
	previousKeyboardState_ = currentKeyboardState_;
}

void Input::updateKeyboardState()
{
	previousKeyboardState_ = currentKeyboardState_;
	currentKeyboardState_ = SDL_GetKeyboardState(NULL);
}
