#pragma once

#include "../core//ActorComponent.h"

class Sprite : public ActorComponent 
{
public:
	Sprite(Actor& actor);
	~Sprite();
};