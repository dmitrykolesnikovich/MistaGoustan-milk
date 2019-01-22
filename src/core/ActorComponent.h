#ifndef _ACTOR_COMPONENT_H
#define _ACTOR_COMPONENT_H

enum ComponentType
{
	SCRIPT = 1 << 0,
	SPRITE = 1 << 1,
	ANIMATOR = 1 << 2,
	BOX_COLLIDER = 1 << 3,
	VELOCITY = 1 << 4,
	MAX_COMPONENTS = 1 << 31
};

class Actor;
class ResourceManager;

class ActorComponent
{
public:
	explicit ActorComponent(Actor& actor);
	virtual ~ActorComponent() = default;

	// Returns the components actor.
	Actor& actor() const;

protected:
	Actor& actor_;
};

#endif
