#ifndef _VELOCITY_
#define _VELOCITY_

#include "../core/ActorComponent.h"

#include "../math/Vector2d.h"

// All objects that move should own a velocity component.
// In regards to movement, directly setting an objects position is ill advised as the collision system operates on Velocity.
class Velocity : public ActorComponent
{
public:
	static const ComponentType type;

	Velocity(Actor& actor);
	~Velocity();

	// Set the velocity.
	void setVelocity(float x, float y);

	// Set the velocity.
	void setVelocity(Vector2d velocity);

	// Get the velocity.
	Vector2d getVelocity() const;

private:
	Vector2d value_;
};

#endif
