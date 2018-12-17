#pragma once

#include <string>

#include "GameObject.h"

union SDL_Event;

class Player : public GameObject
{
public:
	Player(const std::string& name);
	~Player();

	void handleEvent(SDL_Event& e) override;
	void update() override;

protected:
	Vector2d _input;

private:
	const int SPEED = 2;
};
