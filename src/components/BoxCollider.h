#ifndef _BOX_COLLIDER_
#define _BOX_COLLIDER_

#include "SDL.h"

#include "../core/ActorComponent.h"

class BoxCollider : public ActorComponent
{
public:
	static const ComponentType type;

	BoxCollider(Actor& actor);
	~BoxCollider();

	void updateBBox();

	SDL_Rect rect() const;

	int width() const;
	int height() const;

	void width(int width);
	void height(int height);

	bool overlaps(SDL_Rect otherRect) const;
	bool overlaps(SDL_Rect otherRect, SDL_Rect* result) const;

private:
	SDL_Rect rect_;
};

#endif
