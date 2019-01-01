#include "SystemManager.h"

void SystemManager::init(SystemManagerParams& params)
{
#ifdef _DEBUG
	debugRenderer_ = std::unique_ptr<DebugRenderer>(new DebugRenderer(params.renderer));
#endif

	logicSystem_ = std::unique_ptr<Logic>(new Logic(params.luaState));
	physicsSystem_ = std::unique_ptr<Physics>(new Physics(params.eventQueue));
	renderSystem_ = std::unique_ptr<Renderer>(new Renderer(params.renderer, params.resourceManager));
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

void SystemManager::handleActorEvent(ActorEvent& gameEvent)
{
#ifdef _DEBUG
	debugRenderer_->handleEvent(gameEvent);
#endif

	physicsSystem_->handleEvent(gameEvent);
	renderSystem_->handleEvent(gameEvent);

	// The logic system can depend on resources loaded by other systems, so let the other systems handle their events first.
	logicSystem_->handleEvent(gameEvent);
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
	logicSystem_.release();
	physicsSystem_.release();
	renderSystem_.release();
	debugRenderer_.release();
}
