project(milklib)

set(MILK_SRC_FILES
        # core
        core/Actor.cpp
        core/Actor.h
        core/ActorComponent.cpp
        core/ActorComponent.h
        core/Game.h
        core/Game.cpp
        core/Scene.cpp
        core/Scene.h

        # events
        systems/events/EventQueue.cpp
        systems/events/EventQueue.h
        systems/events/GameEvents.h

        # externals
        externals/json.hpp
        externals/sol.hpp

        # math
        math/Vector2d.h

        # graphics
        systems/graphics/Animator.cpp
        systems/graphics/Animator.h
        systems/graphics/Graphics.cpp
        systems/graphics/Graphics.h
        systems/graphics/Sprite.cpp
        systems/graphics/Sprite.h

        # physics
        systems/physics/BoxCollider.cpp
        systems/physics/BoxCollider.h
        systems/physics/Physics.cpp
        systems/physics/Physics.h
        systems/physics/SpatialPartitionGrid.cpp
        systems/physics/SpatialPartitionGrid.h
        systems/physics/Velocity.cpp
        systems/physics/Velocity.h

        # scripting
        systems/scripting/api/LuaHandleRegistry.h
        systems/scripting/api/LuaActor.cpp
        systems/scripting/api/LuaActor.h
        systems/scripting/api/LuaGame.cpp
        systems/scripting/api/LuaGame.h
        systems/scripting/api/LuaScene.cpp
        systems/scripting/api/LuaScene.h
        systems/scripting/api/LuaCollisionEvent.cpp
        systems/scripting/api/LuaCollisionEvent.h
        systems/scripting/Logic.cpp
        systems/scripting/Logic.h
        systems/scripting/Script.cpp
        systems/scripting/Script.h

        # tools
        systems/tools/DebugTools.cpp
        systems/tools/DebugTools.h

        # tilemap
        tilemap/Tilemap.h

        # utilities
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
        utilities/SceneManager.cpp
        utilities/SceneManager.h
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