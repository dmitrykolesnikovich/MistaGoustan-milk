#include "PlayerBehavior.h"

#include "../core/Actor.h"
#include "../components/Velocity.h"
#include "../utilities//Input.h"
#include "../math/Vector2d.h"

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

	if (Input::getKey(SDL_SCANCODE_UP))
		input.y = -1;
	if (Input::getKey(SDL_SCANCODE_DOWN))
		input.y = 1;
	if (Input::getKey(SDL_SCANCODE_LEFT))
		input.x = -1;
	if (Input::getKey(SDL_SCANCODE_RIGHT))
		input.x = 1;

	if (magnitude(input) > 1.f)
		input = normalize(input);

	Vector2d velocity = input * speed;

	vel_->setVelocity(velocity);
}
