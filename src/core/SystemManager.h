#ifndef _SYSTEM_MANAGER_
#define _SYSTEM_MANAGER_

#include <memory>

#ifdef _DEBUG
#include "../systems/DebugRenderer.h"
#endif

#include "../systems/ActorEventQueue.h"
#include "../systems/Logic.h"
#include "../systems/Renderer.h"
#include "../systems/Physics.h"

namespace sol 
{
	class state;
}

class Actor;
class ActorEventQueue;
class ActorEvent;
class ResourceManager;
class Scene;

struct SDL_Renderer;

struct SystemManagerParams 
{
	sol::state& luaState;
	ActorEventQueue& eventQueue;
	SDL_Renderer& renderer;
	ResourceManager& resourceManager;
};

class SystemManager
{
public:
	SystemManager() = default;
	~SystemManager() = default;

	void init(SystemManagerParams& params);

	void handleInputEvent(SDL_Event& inputEvent);

	void handleGameEvent(ActorEvent& gameEvent);

	void update();

	void render(Scene& scene);

	void unload();

private:
#ifdef _DEBUG
	std::unique_ptr<DebugRenderer> debugRenderer_;
#endif

	std::unique_ptr<Logic> logicSystem_;
	std::unique_ptr<Physics> physicsSystem_;
	std::unique_ptr<Renderer> renderSystem_;
};

#endif