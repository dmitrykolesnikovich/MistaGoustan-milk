#ifndef _SYSTEM_
#define _SYSTEM_

class Actor;
class Scene;

class System
{
public:
	virtual void onActorAdded(Actor& actor) = 0;
	virtual void onActorDestroyed(Actor& actor) = 0;
	virtual void onActorModified(Actor& actor) = 0;

	virtual void update(Scene& scene) = 0;
};

#endif
