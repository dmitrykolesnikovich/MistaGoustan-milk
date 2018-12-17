#ifndef _COMPONENT_
#define _COMPONENT_

enum class ComponentType 
{
	SPRITE = 0,
	ANIMATOR = 1,
	COLLIDER = 2
};

class ResourceManager;

class Component
{
public:
	Component() = default;

	virtual void init(ResourceManager& resourceManager) 
	{
	}

	virtual void begin() 
	{
	}

	virtual void update()
	{
	}

	virtual void end() 
	{
	}
};

#endif
