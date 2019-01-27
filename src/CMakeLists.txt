project(milklib)

set(MILK_SRC_FILES

        # debug tools
        debugtools/DebugTools.cpp
        debugtools/DebugTools.h

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
        graphics/TextureLoader.cpp
        graphics/TextureLoader.h
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

        # runtime
        runtime/Game.h
        runtime/Game.cpp

        #scene
        scene/Actor.cpp
        scene/Actor.h
        scene/ActorComponent.cpp
        scene/ActorComponent.h
        scene/Scene.cpp
        scene/Scene.h
        scene/SceneLoader.cpp
        scene/SceneLoader.h
        scene/SceneManager.cpp
        scene/SceneManager.h

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

        # utilities
        utilities/Alignment.h
        utilities/AssetLoader.h
        utilities/IdGenerator.cpp
        utilities/IdGenerator.h
        utilities/ResourceManager.cpp
        utilities/ResourceManager.h
        utilities/Timer.cpp
        utilities/Timer.h

        # window
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