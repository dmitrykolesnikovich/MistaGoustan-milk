#ifndef MILK_LUA_HANDLE_REGISTRY_
#define MILK_LUA_HANDLE_REGISTRY_

#include "externals/sol.hpp"

#include "LuaActor.h"
#include "LuaGame.h"
#include "LuaScene.h"
#include "LuaCollisionEvent.h"

#include "scene/Actor.h"
#include "scene/Scene.h"
#include "runtime/Game.h"
#include "math/Vector2d.h"
#include "input/Keyboard.h"
#include "window/Window.h"
#include "physics/BoxCollider.h"
#include "events/GameEvents.h"

namespace milk
{
    // Registry for the Lua API.
    class LuaHandleRegistry
    {
    public:
        static void RegisterHandles(sol::state& luaState)
        {
            using namespace milk;

            // Input
            /////////////////////////////////////////////////////////////////
            luaState.new_enum("Keys",
                              "A", SDLK_a,
                              "D", SDLK_d,
                              "F", SDLK_f,
                              "R", SDLK_r,
                              "S", SDLK_s,
                              "W", SDLK_w,
                              "Tilde", SDLK_BACKQUOTE);

            // Actor
            /////////////////////////////////////////////////////////////////
            luaState.new_usertype<Actor>("Actor",
                                         "name", sol::readonly_property(&lua::actor::name),
                                         "move", &lua::actor::move,
                                         "set_animation", &lua::actor::setAnimation,
                                         "flip_x", &lua::actor::flipX,
                                         "flip_y", &lua::actor::flipY);

            // Collision Event
            /////////////////////////////////////////////////////////////////
            luaState.new_usertype<ActorCollisionEvent>("ActorCollisionEvent",
                                                       "other",
                                                       sol::readonly_property(&lua::collision_event::other));

            // Input
            /////////////////////////////////////////////////////////////////
            luaState.new_usertype<Keyboard>("Input",
                                            "get_key", &Keyboard::getKey,
                                            "get_key_pressed", &Keyboard::getKeyPressed,
                                            "get_key_released", &Keyboard::getKeyReleased);

            // Game
            /////////////////////////////////////////////////////////////////
            luaState.new_usertype<Game>("Game",
                                        "window", sol::readonly_property(&lua::game::window),
                                        "scene", sol::readonly_property(&lua::game::scene),
                                        "load_scene", &lua::game::loadScene);

            luaState.new_usertype<Scene>("Scene",
                                         "set_cam_target", &lua::scene::setCameraTarget);

            // Vector2D
            /////////////////////////////////////////////////////////////////
            luaState.new_usertype<Vector2d>("Vector2D",
                                            sol::constructors<Vector2d(), Vector2d(int, int)>(),
                                            "x", &Vector2d::x,
                                            "y", &Vector2d::y,
                                            "magnitude", &Vector2d::magnitude,
                                            "normalize", &Vector2d::normalize,
                                            sol::meta_function::equal_to, &Vector2d::operator==,
                                            sol::meta_function::multiplication, &Vector2d::operator*);

            // Window
            /////////////////////////////////////////////////////////////////
            luaState.new_usertype<Window>("Window",
                                          "toggle_fullscreen", &Window::toggleFullscreen);
        }
    };
}

#endif
