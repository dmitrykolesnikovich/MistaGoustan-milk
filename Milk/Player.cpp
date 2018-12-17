#include "Player.h"

#include "SDL_events.h"

Player::Player(const std::string& name)
	: GameObject(name)
{
}

Player::~Player()
{
}

void Player::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_UP: _input.y = -1; break;
			case SDLK_DOWN: _input.y = 1; break;
			case SDLK_LEFT: _input.x = -1; break;
			case SDLK_RIGHT: _input.x = 1; break;
		}
	}

	if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_UP: _input.y = 0; break;
			case SDLK_DOWN: _input.y = 0; break;
			case SDLK_LEFT: _input.x = 0; break;
			case SDLK_RIGHT: _input.x = 0; break;
		}
	}
}

void Player::update()
{
	if (magnitude(_input) > 1.0f)
		_input = normalize(_input);

	velocity = _input * SPEED;

	position.x += velocity.x;
	position.y += velocity.y;
}
