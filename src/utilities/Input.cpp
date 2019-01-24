#include "Input.h"

#include <iostream>
#include <cstring>

Uint8 Input::previousState_[SDL_NUM_SCANCODES];
Uint8 Input::currentState_[SDL_NUM_SCANCODES];

bool Input::getKey(SDL_Keycode keycode) {
    return currentState_[SDL_GetScancodeFromKey(keycode)];
}

bool Input::getKeyPressed(SDL_Keycode keycode) {
    return currentState_[SDL_GetScancodeFromKey(keycode)] && !previousState_[SDL_GetScancodeFromKey(keycode)];
}

bool Input::getKeyReleased(SDL_Keycode keycode) {
    return !currentState_[SDL_GetScancodeFromKey(keycode)] && previousState_[SDL_GetScancodeFromKey(keycode)];
}

void Input::initialize() {
    std::memset(previousState_, 0, sizeof(Uint8) * SDL_NUM_SCANCODES);
    std::memcpy(currentState_, SDL_GetKeyboardState(NULL), sizeof(Uint8) * SDL_NUM_SCANCODES);
}

void Input::updateKeyboardState() {
    std::memcpy(previousState_, currentState_, sizeof(Uint8) * SDL_NUM_SCANCODES);
    std::memcpy(currentState_, SDL_GetKeyboardState(NULL), sizeof(Uint8) * SDL_NUM_SCANCODES);
}
