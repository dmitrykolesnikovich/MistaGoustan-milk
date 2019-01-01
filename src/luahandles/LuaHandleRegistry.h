#ifndef _LUA_HANDLE_REGISTRY_
#define _LUA_HANDLE_REGISTRY_

#include "../externals/sol.hpp"

#include "LuaHandle_Actor.h"
#include "LuaHandle_CollisionEvent.h"
#include "LuaHandle_BoxCollider.h"

#include "../core/Game.h"
#include "../math/Vector2d.h"
#include "../utilities/Input.h"
#include "../utilities/Window.h"
#include "../components/BoxCollider.h"

// Registry for the Lua API.
static class LuaHandleRegistry
{
public:
	static void RegisterHandles(sol::state& luaState)
	{
		luaState.new_usertype<LuaHandle_Actor>("Actor",
			"name", sol::readonly_property(&LuaHandle_Actor::name),
			"move", &LuaHandle_Actor::move,
			"set_animation", &LuaHandle_Actor::setAnimation,
			"flip_x", &LuaHandle_Actor::flipX,
			"flip_y", &LuaHandle_Actor::flipY,
			"make_cam_target", &LuaHandle_Actor::setAsCameraTarget);

		luaState.new_usertype<LuaHandle_CollisionEvent>("CollisionEvent",
			"other", sol::readonly_property(&LuaHandle_CollisionEvent::other));

		luaState.new_usertype<LuaHandle_BoxCollider>("BoxCollider",
			"actor", sol::readonly_property(&LuaHandle_BoxCollider::actor));

		luaState.new_usertype<Input>("Input",
			"get_key", &Input::getKey,
			"get_key_pressed", &Input::getKeyPressed,
			"get_key_released", &Input::getKeyReleased);

		luaState.new_usertype<Vector2d>("Vector2D",
			sol::constructors<Vector2d(), Vector2d(int, int)>(),
				"x", &Vector2d::x,
				"y", &Vector2d::y,
				"magnitude", &Vector2d::magnitude,
				"normalize", &Vector2d::normalize,
				sol::meta_function::equal_to, &Vector2d::operator==,
				sol::meta_function::multiplication, &Vector2d::operator*);

		luaState.new_usertype<Window>("Window",
			sol::constructors<Window()>(),
				"toggle_fullscreen", &Window::toggleFullscreen);

		luaState.new_usertype<Game>("Game",
			sol::constructors<Game()>(),
				"window", sol::readonly_property(&Game::window),
				"loadScene", &Game::loadScene);
	}
};

#endif
