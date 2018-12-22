#pragma once

class Scene;

class System 
{
public:
	System();
	~System();

	virtual void update(Scene& scene) = 0;
};