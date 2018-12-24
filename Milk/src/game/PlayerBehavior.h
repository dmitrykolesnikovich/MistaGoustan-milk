#pragma once

#include "../components/Behavior.h"

class Velocity;

class PlayerBehavior : public Behavior
{
public:
	static const ComponentType type;

	PlayerBehavior(Actor& actor);
	~PlayerBehavior() = default;

	void begin() override;

private:
	Velocity* vel_;
};