project(milklib)

set(MILK_SRC_FILES
        components/Animator.cpp
        components/Animator.h
        components/BoxCollider.cpp
        components/BoxCollider.h
        components/Script.cpp
        components/Script.h
        components/Sprite.cpp
        components/Sprite.h
        components/Velocity.cpp
        components/Velocity.h
        core/Actor.cpp
        core/Actor.h
        core/ActorComponent.cpp
        core/ActorComponent.h
        core/Game.h
        core/Game.cpp
        core/Scene.cpp
        core/Scene.h
        externals/json.hpp
        externals/sol.hpp
        luahandles/LuaHandleRegistry.h
        luahandles/LuaActor.cpp
        luahandles/LuaActor.h
        luahandles/LuaGame.cpp
        luahandles/LuaGame.h
        luahandles/LuaScene.cpp
        luahandles/LuaScene.h
        luahandles/LuaCollisionEvent.cpp
        luahandles/LuaCollisionEvent.h
        math/Vector2d.h
        systems/DebugTools.cpp
        systems/DebugTools.h
        systems/EventQueue.cpp
        systems/EventQueue.h systems/GameEvents.h
        systems/Logic.cpp
        systems/Logic.h
        systems/Physics.cpp
        systems/Physics.h
        systems/Graphics.cpp
        systems/Graphics.h
        utilities/SceneManager.cpp
        utilities/SceneManager.h
        systems/SpatialPartitionGrid.cpp
        systems/SpatialPartitionGrid.h
        tilemap/Tilemap.h
        utilities/Alignment.h
        utilities/Camera.cpp
        utilities/Camera.h
        utilities/IdGenerator.cpp
        utilities/IdGenerator.h
        utilities/Input.cpp
        utilities/Input.h
        utilities/ResourceManager.cpp
        utilities/ResourceManager.h
        utilities/SceneLoader.cpp
        utilities/SceneLoader.h
        utilities/Texture.cpp
        utilities/Texture.h
        utilities/Timer.cpp
        utilities/Timer.h
        utilities/Window.cpp
        utilities/Window.h)

add_library(milklib ${MILK_SRC_FILES})

# include lib headers
target_include_directories(milklib
        PUBLIC
            ${SDL_INCLUDE_DIR}
            ${SDL2_IMAGE_INCLUDE_DIRS}
            ${LUA53_INCLUDE_DIR}
            ${milklib_SOURCE_DIR}
        )

# link libs
target_link_libraries(milklib
        PUBLIC
            ${SDL2_LIBRARY}
            ${SDL2_IMAGE_LIBRARIES}
            ${LUA53_LIBRARIES}
        PRIVATE
            # Include code-coverage settings
            coverage_config
        )