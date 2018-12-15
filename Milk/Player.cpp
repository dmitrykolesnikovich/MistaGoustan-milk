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
			case SDLK_UP: _yVelocity -= SPEED; break;
			case SDLK_DOWN: _yVelocity += SPEED; break;
			case SDLK_LEFT: _xVelocity -= SPEED; break;
			case SDLK_RIGHT: _xVelocity += SPEED; break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_UP: _yVelocity += SPEED; break;
			case SDLK_DOWN: _yVelocity -= SPEED; break;
			case SDLK_LEFT: _xVelocity += SPEED; break;
			case SDLK_RIGHT: _xVelocity -= SPEED; break;
		}
	}
}

void Player::update()
{
	_xPosition += _xVelocity;
	_yPosition += _yVelocity;
}
