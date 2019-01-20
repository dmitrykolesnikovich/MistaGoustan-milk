#ifndef _INPUT_
#define _INPUT_

#include "SDL.h"

class Input
{
public:
	Input() = default;

	// Returns true if given key is down.
	static bool getKey(SDL_Keycode keycode);

	// Returns true if given key has been pressed.
	static bool getKeyPressed(SDL_Keycode keycode);

	// Returns true if given key has been released.
	static bool getKeyReleased(SDL_Keycode keycode);

	// Initializes the key states.
	static void initialize();

	// Updates the key states.
	static void updateKeyboardState();

private:
	static Uint8 previousState_[SDL_NUM_SCANCODES];
	static Uint8 currentState_[SDL_NUM_SCANCODES];
};

#endif
