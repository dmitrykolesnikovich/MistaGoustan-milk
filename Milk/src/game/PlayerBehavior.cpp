#include "PlayerBehavior.h"

#include "../core/Actor.h"
#include "../components/Velocity.h"
#include "../utilities//Input.h"
#include "../math/Vector2d.h"

#include <iostream>

const ComponentType PlayerBehavior::type = BEHAVIOR;

PlayerBehavior::PlayerBehavior(Actor& actor)
	: Behavior::Behavior(actor)
{
}

void PlayerBehavior::begin()
{
	vel_ = actor_.getComponent<Velocity>();	
}

void PlayerBehavior::update()
{
	const float speed = 3.f;
	Vector2d input = Vector2d(0, 0);

	if (Input::getKeyPressed(SDLK_SPACE, &prevSpace_))
		std::cout << "pressed" << std::endl;

	if (Input::getKey(SDLK_w))
		input.y = -1;
	if (Input::getKey(SDLK_s))
		input.y = 1;
	if (Input::getKey(SDLK_a))
		input.x = -1;
	if (Input::getKey(SDLK_d))
		input.x = 1;

	if (magnitude(input) > 1.f)
		input = normalize(input);

	Vector2d velocity = input * speed;

	vel_->setVelocity(velocity);
}
