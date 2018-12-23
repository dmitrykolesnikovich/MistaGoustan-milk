#ifndef _COMPONENT_TYPE_
#define _COMPONENT_TYPE_

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
class ResourceManager;

class ActorComponent
{
public:
	ActorComponent(Actor& actor);
	virtual ~ActorComponent();

	// Returns the components actor.
	Actor& getActor();

protected:
	Actor& actor_;
};

#endif
