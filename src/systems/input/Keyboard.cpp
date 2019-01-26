#include "Keyboard.h"

#include <iostream>
#include <cstring>

Uint8 Keyboard::previousState_[SDL_NUM_SCANCODES];
Uint8 Keyboard::currentState_[SDL_NUM_SCANCODES];

bool Keyboard::getKey(SDL_Keycode keycode) {
    return currentState_[SDL_GetScancodeFromKey(keycode)];
}

bool Keyboard::getKeyPressed(SDL_Keycode keycode) {
    return currentState_[SDL_GetScancodeFromKey(keycode)] && !previousState_[SDL_GetScancodeFromKey(keycode)];
}

bool Keyboard::getKeyReleased(SDL_Keycode keycode) {
    return !currentState_[SDL_GetScancodeFromKey(keycode)] && previousState_[SDL_GetScancodeFromKey(keycode)];
}

void Keyboard::initialize() {
    std::memset(previousState_, 0, sizeof(Uint8) * SDL_NUM_SCANCODES);
    std::memcpy(currentState_, SDL_GetKeyboardState(NULL), sizeof(Uint8) * SDL_NUM_SCANCODES);
}

void Keyboard::updateKeyboardState() {
    std::memcpy(previousState_, currentState_, sizeof(Uint8) * SDL_NUM_SCANCODES);
    std::memcpy(currentState_, SDL_GetKeyboardState(NULL), sizeof(Uint8) * SDL_NUM_SCANCODES);
}
