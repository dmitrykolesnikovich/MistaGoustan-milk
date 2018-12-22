#pragma once

enum ComponentType 
{
	BEHAVIOR = 1 << 0,
	SPRITE = 1 << 1,
	ANIMATOR = 1 << 2,
	BOX_COLLIDER = 1 << 3,
	VELOCITY = 1 << 4,
	MAX_COMPONENTS = 1 << 32
};

class Actor;

class ActorComponent 
{
public:
	ActorComponent(Actor& actor);
	virtual ~ActorComponent();

protected:
	Actor& _actor;
};