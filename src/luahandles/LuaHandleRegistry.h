#ifndef _LUA_HANDLE_REGISTRY_
#define _LUA_HANDLE_REGISTRY_

#include "../externals/sol.hpp"

#include "LuaHandle_Actor.h"

#include "../core/Game.h"
#include "../math/Vector2d.h"
#include "../utilities/Input.h"
#include "../utilities/Window.h"

// Registry for the Lua API.
static class LuaHandleRegistry
{
public:
	static void RegisterHandles(sol::state& luaState)
	{
		luaState.new_usertype<LuaHandle_Actor>("actor",
			"move", &LuaHandle_Actor::move,
			"set_animation", &LuaHandle_Actor::setAnimation,
			"flip_x", &LuaHandle_Actor::flipX,
			"flip_y", &LuaHandle_Actor::flipY);

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
