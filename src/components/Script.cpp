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
	luaScript_.set("actor", LuaHandle_Actor(actor_));
}

void Script::begin()
{
	sol::table self = luaScript_;
	luaScript_["begin"](self);
}

void Script::update() 
{
	sol::table self = luaScript_;
	luaScript_["update"](self);
}

void Script::end() 
{
	sol::table self = luaScript_;
	luaScript_["destroyed"](self);
}