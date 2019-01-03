#include <memory>

#include <memory>

#include "SystemManager.h"

ActorEventQueue& SystemManager::actorEventQueue()
{
	return actorEventQueue_;
}

void SystemManager::init(SystemManagerParams& params)
{
#ifdef _DEBUG
	debugRenderer_ = std::make_unique<DebugRenderer>(params.renderer);
#endif

	logicSystem_ = std::make_unique<Logic>(params.luaState);
	physicsSystem_ = std::make_unique<Physics>(actorEventQueue_);
	renderSystem_ = std::make_unique<Renderer>(params.renderer, params.resourceManager);
}

void SystemManager::handleInputEvent(SDL_Event& inputEvent)
{
	switch (inputEvent.type)
	{
	case SDL_KEYUP:
#ifdef _DEBUG
		if (inputEvent.key.keysym.sym == SDLK_BACKQUOTE)
			debugRenderer_->show = !debugRenderer_->show;
#endif
		break;
	}
}

void SystemManager::handleActorEvents()
{
	while (!actorEventQueue_.empty()) 
	{
		auto gameEvent = actorEventQueue_.popEvent();

#ifdef _DEBUG
		debugRenderer_->handleEvent(*gameEvent);
#endif

		physicsSystem_->handleEvent(*gameEvent);
		renderSystem_->handleEvent(*gameEvent);

		// The logic system can depend on resources loaded by other systems, so let the other systems handle their events first.
		logicSystem_->handleEvent(*gameEvent);
	}
}

void SystemManager::update()
{
	logicSystem_->update();
	physicsSystem_->update();
}

void SystemManager::render(Scene& scene)
{
	renderSystem_->render(scene);

#ifdef _DEBUG
	debugRenderer_->render(scene);
#endif
}

void SystemManager::unload()
{
	logicSystem_.reset();
	physicsSystem_.reset();
	renderSystem_.reset();

#ifdef _DEBUG
	debugRenderer_.reset();
#endif
}
