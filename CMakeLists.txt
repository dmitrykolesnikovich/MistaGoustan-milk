cmake_minimum_required(VERSION 3.13)

project(Milk)

# third party dlls are included via environment vars
# example of install path (windows) C:\thirdparty\SDL2-2.0.9
# should the project files just contain the dependencies and then we can use explicit paths?
set(SDL2_PATH $ENV{SDL_DIR})
set(SDL_image_PATH $ENV{SDL_image_DIR})
set(LUA_PATH $ENV{LUA_DIR})

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

#copy res file and libs to output binary
file(COPY res DESTINATION ${CMAKE_BINARY_DIR})
file(GLOB LIBS "libs/*.dll")
file(COPY ${LIBS} DESTINATION ${CMAKE_BINARY_DIR})