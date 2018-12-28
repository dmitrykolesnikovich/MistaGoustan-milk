#include "Behavior.h"

#include "../core/Actor.h"

const ComponentType Behavior::type = BEHAVIOR;

Behavior::Behavior(Actor& actor)
	: ActorComponent::ActorComponent(actor)
{
}

Behavior::~Behavior()
{
}

void Behavior::script(const std::string& scriptName) 
{
	scriptName_ = scriptName;
}

void Behavior::load(sol::state& luaState)
{
	luaBehavior_ = luaState.script_file(scriptName_);
	luaBehavior_.set("actor", &actor_);
}

void Behavior::begin()
{
	luaBehavior_["begin"](luaBehavior_);
}

void Behavior::update() 
{
	luaBehavior_["update"](luaBehavior_);
}

void Behavior::end() 
{
	luaBehavior_["destroyed"](luaBehavior_);
}