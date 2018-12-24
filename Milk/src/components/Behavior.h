#ifndef _BEHAVIOR_
#define _BEHAVIOR_

#include "../core/ActorComponent.h"

class Behavior : public ActorComponent
{
public:
	static const ComponentType type;

	Behavior(Actor& actor);
	~Behavior();

	virtual void begin();
	virtual void update();
	virtual void end();
};

#endif // !_BEHAVIOR_
