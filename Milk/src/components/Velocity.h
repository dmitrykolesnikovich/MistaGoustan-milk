#ifndef _VELOCITY_
#define _VELOCITY_

#include "../core/ActorComponent.h"

#include "../math/Vector2d.h"

class Velocity : public ActorComponent
{
public:
	static const ComponentType type;

	Velocity(Actor& actor);
	~Velocity();

	void setVelocity(float x, float y);

	void setVelocity(Vector2d velocity);

	Vector2d getVelocity() const;

private:
	Vector2d value_;
};

#endif
