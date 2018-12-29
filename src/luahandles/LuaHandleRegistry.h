#ifndef _LUA_HANDLE_REGISTRY_
#define _LUA_HANDLE_REGISTRY_

#include "../externals/sol.hpp"

#include "LuaHandle_Actor.h"

#include "../core/Game.h"
#include "../math/Vector2d.h"
#include "../utilities/Input.h"
#include "../utilities/Window.h"

static class LuaHandleRegistry
{
public:
	static void RegisterHandles(sol::state& luaState)
	{
		luaState.new_usertype<LuaHandle_Actor>("actor",
			"move", &LuaHandle_Actor::move);

		luaState.new_usertype<Input>("Input",
			"getKey", &Input::getKey);

		luaState.new_usertype<Vector2d>("Vector2D",
			sol::constructors<Vector2d(), Vector2d(int, int)>(),
				"x", &Vector2d::x,
				"y", &Vector2d::y);

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
