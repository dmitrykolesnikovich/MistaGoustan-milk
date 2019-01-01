#include "Script.h"

#include "../core/Actor.h"

#include "../luahandles/LuaHandle_Actor.h"

const ComponentType Script::type = SCRIPT;

Script::Script(Actor& actor)
	: ActorComponent::ActorComponent(actor)
{
}

void Script::script(const std::string& scriptName) 
{
	scriptName_ = scriptName;
}

void Script::load(sol::state& luaState)
{
	luaScript_ = luaState.script_file(scriptName_);

	// Set "self.actor"
	luaScript_.set("actor", LuaHandle_Actor(actor_));
}

void Script::begin()
{
	sol::function onCollision = luaScript_[SCRIPT_CALLBACK_BEGIN];

	if (!onCollision.valid())
		return;

	sol::table self = luaScript_;
	luaScript_[SCRIPT_CALLBACK_BEGIN](self);
}

void Script::update() 
{
	sol::function onCollision = luaScript_[SCRIPT_CALLBACK_UPDATE];

	if (!onCollision.valid())
		return;

	sol::table self = luaScript_;
	luaScript_[SCRIPT_CALLBACK_UPDATE](self);
}

void Script::onCollision(ActorCollisionEvent& collisionEvent)
{
	sol::function onCollision = luaScript_[SCRIPT_CALLBACK_ON_COLLISION];

	if (!onCollision.valid())
		return;

	sol::table self = luaScript_;
	luaScript_[SCRIPT_CALLBACK_ON_COLLISION](self, collisionEvent);
}

void Script::end() 
{
	sol::function onCollision = luaScript_[SCRIPT_CALLBACK_END];

	if (!onCollision.valid())
		return;

	sol::table self = luaScript_;
	luaScript_[SCRIPT_CALLBACK_END](self);
}
