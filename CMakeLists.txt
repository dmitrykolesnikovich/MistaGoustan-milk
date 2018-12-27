cmake_minimum_required(VERSION 3.13)

project(Milk)

# third party dlls are included via environment vars
# example of install path (windows) C:\thirdparty\SDL2-2.0.9
# should the project files just contain the dependencies and then we can use explicit paths?
set(SDL2_DIR thirdparty/SDL2-2.0.9)
set(SDL_IMAGE_DIR thirdparty/SDL2_image-2.0.4)
set(LUA_DIR thirdparty/Lua-5.3.4)

get_filename_component(SDL2_PATH ${SDL2_DIR} ABSOLUTE)
get_filename_component(SDL_image_PATH ${SDL_IMAGE_DIR} ABSOLUTE)
get_filename_component(LUA_PATH ${LUA_DIR} ABSOLUTE)

include_directories(${SDL2_PATH}/include)
include_directories(${SDL_image_PATH}/include)
include_directories(${LUA_PATH}/include)

link_directories(${SDL2_PATH}/lib/x86)
link_directories(${SDL_image_PATH}/lib/x86)
link_directories(${LUA_PATH})

#create the project that compiles to an exe
add_executable(Milk src/main.cpp)

# add lib files to link
target_link_libraries(Milk ${SDL2_PATH}/lib/x86/SDL2.lib)
target_link_libraries(Milk ${SDL2_PATH}/lib/x86/SDL2main.lib)
target_link_libraries(Milk ${SDL_image_PATH}/lib/x86/SDL2_image.lib)
target_link_libraries(Milk ${LUA_PATH}/liblua53.a)

# have each subdirectory add its own source files to project
add_subdirectory(src/components)
add_subdirectory(src/core)
add_subdirectory(src/externals)
add_subdirectory(src/luahandles)
add_subdirectory(src/math)
add_subdirectory(src/systems)
add_subdirectory(src/tilemap)
add_subdirectory(src/utilities)

# create filters for IDE
source_group(components REGULAR_EXPRESSION "src/components/*")
source_group(core REGULAR_EXPRESSION "src/core/*")
source_group(externals REGULAR_EXPRESSION "src/externals/*")
source_group(luahandles REGULAR_EXPRESSION "src/luahandles/*")
source_group(math REGULAR_EXPRESSION "src/math/*")
source_group(systems REGULAR_EXPRESSION "src/systems/*")
source_group(tilemap REGULAR_EXPRESSION "src/tilemap/*")
source_group(utilities REGULAR_EXPRESSION "src/utilities/*")

#copy res file to output binary
file(COPY res DESTINATION ${CMAKE_BINARY_DIR})

# copy dlls to output binary
file(GLOB SDL_LIBS "${SDL2_PATH}/lib/x86/*.dll")
file(GLOB SDL_IMAGE_LIBS "${SDL_image_PATH}/lib/x86/*.dll")
file(GLOB LUA_LIBS "${LUA_PATH}/*.dll")

file(COPY ${SDL_LIBS} DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${SDL_IMAGE_LIBS} DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${LUA_LIBS} DESTINATION ${CMAKE_BINARY_DIR})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Milk)