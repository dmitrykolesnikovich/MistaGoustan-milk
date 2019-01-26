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
        events/EventQueue.cpp
        events/EventQueue.h
        events/GameEvents.h

        # externals
        externals/json.hpp
        externals/sol.hpp

        # input
        input/Keyboard.cpp
        input/Keyboard.h

        # graphics
        graphics/Animator.cpp
        graphics/Animator.h
        graphics/Camera.cpp
        graphics/Camera.h
        graphics/Graphics.cpp
        graphics/Graphics.h
        graphics/Sprite.cpp
        graphics/Sprite.h
        graphics/Texture.cpp
        graphics/Texture.h
        graphics/Tilemap.h

        # math
        math/Vector2d.h

        # physics
        physics/BoxCollider.cpp
        physics/BoxCollider.h
        physics/Physics.cpp
        physics/Physics.h
        physics/SpatialPartitionGrid.cpp
        physics/SpatialPartitionGrid.h
        physics/Velocity.cpp
        physics/Velocity.h

        # scripting
        scripting/api/LuaHandleRegistry.h
        scripting/api/LuaActor.cpp
        scripting/api/LuaActor.h
        scripting/api/LuaGame.cpp
        scripting/api/LuaGame.h
        scripting/api/LuaScene.cpp
        scripting/api/LuaScene.h
        scripting/api/LuaCollisionEvent.cpp
        scripting/api/LuaCollisionEvent.h
        scripting/Logic.cpp
        scripting/Logic.h
        scripting/Script.cpp
        scripting/Script.h

        # tools
        tools/DebugTools.cpp
        tools/DebugTools.h

        # utilities
        utilities/Alignment.h
        utilities/IdGenerator.cpp
        utilities/IdGenerator.h
        utilities/ResourceManager.cpp
        utilities/ResourceManager.h
        utilities/SceneLoader.cpp
        utilities/SceneLoader.h
        utilities/SceneManager.cpp
        utilities/SceneManager.h
        utilities/Timer.cpp
        utilities/Timer.h
        window/Window.cpp
        window/Window.h)

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