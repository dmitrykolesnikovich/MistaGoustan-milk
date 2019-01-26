#include "Script.h"

#include "core/Actor.h"
#include "systems/events/GameEvents.h"

const ComponentType Script::type = SCRIPT;

Script::Script(Actor& actor)
        : ActorComponent::ActorComponent(actor) {
}

void Script::script(const std::string& scriptName) {
    scriptName_ = scriptName;
}

void Script::load(sol::state& luaState) {
    luaScript_ = luaState.script_file(scriptName_);

    // Set "self.actor"
    luaScript_["actor"] = &actor_;
}

void Script::begin() {
    sol::function onBegin = luaScript_[SCRIPT_CALLBACK_BEGIN];

    if (!onBegin.valid())
        return;

    sol::table self = luaScript_;
    luaScript_[SCRIPT_CALLBACK_BEGIN](self);
}

void Script::update() {
    sol::function onUpdate = luaScript_[SCRIPT_CALLBACK_UPDATE];

    if (!onUpdate.valid())
        return;

    sol::table self = luaScript_;
    luaScript_[SCRIPT_CALLBACK_UPDATE](self);
}

void Script::onCollision(ActorCollisionEvent& collisionEvent) {
    sol::function onCollision = luaScript_[SCRIPT_CALLBACK_ON_COLLISION];

    if (!onCollision.valid())
        return;

    sol::table self = luaScript_;
    luaScript_[SCRIPT_CALLBACK_ON_COLLISION](self, collisionEvent);
}

void Script::end() {
    sol::function onEnd = luaScript_[SCRIPT_CALLBACK_END];

    if (!onEnd.valid())
        return;

    sol::table self = luaScript_;
    luaScript_[SCRIPT_CALLBACK_END](self);
}
