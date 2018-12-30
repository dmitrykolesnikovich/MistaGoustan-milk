#include "LuaHandle_Actor.h"

#include "../components/Animator.h"
#include "../components/Sprite.h"
#include "../components/Velocity.h"

#include "../core/Actor.h"
#include "../core/Scene.h"

LuaHandle_Actor::LuaHandle_Actor(Actor& actor)
	: actor_(actor)
{
}

void LuaHandle_Actor::setAsCameraTarget()
{
	auto& scene = actor_.scene();
	scene.camera().setTarget(&actor_);
}

void LuaHandle_Actor::move(float x, float y)
{
	auto velocity = actor_.getComponent<Velocity>();

	if (velocity == nullptr)
		return;

	velocity->value(x, y);
}

void LuaHandle_Actor::setAnimation(const std::string& name)
{
	auto animator = actor_.getComponent<Animator>();

	if (animator == nullptr)
		return;

	animator->setAnimation(name);
}

void LuaHandle_Actor::flipX()
{
	auto sprite = actor_.getComponent<Sprite>();

	if (sprite == nullptr)
		return;

	sprite->flipX();
}

void LuaHandle_Actor::flipY()
{
	auto sprite = actor_.getComponent<Sprite>();

	if (sprite == nullptr)
		return;

	sprite->flipY();
}
