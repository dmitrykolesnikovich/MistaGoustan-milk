cmake_minimum_required(VERSION 3.6.1)

project(Milk)

# we're a c++14 family.
set(CMAKE_CXX_STANDARD 14)

# set the ~/cmake module path for project
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# On windows, you have to point cmake to our third party dependencies.
if (WIN32)

    # path variables that need to be set
    # SDL2_PATH
    # SDL2_IMAGE_PATH

    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

        # provide paths for winGW development libs

    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

        # provide paths for visual c++ development libs

    endif()
endif()

# run find scripts
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(Lua53 REQUIRED)

add_subdirectory(src)

# create solution explorer filters for visual studio
# put main.cpp at the root level
source_group("" FILES "src/main.cpp")
source_group(components REGULAR_EXPRESSION "src/components/*")
source_group(core REGULAR_EXPRESSION "src/core/*")
source_group(externals REGULAR_EXPRESSION "src/externals/*")
source_group(luahandles REGULAR_EXPRESSION "src/luahandles/*")
source_group(math REGULAR_EXPRESSION "src/math/*")
source_group(systems REGULAR_EXPRESSION "src/systems/*")
source_group(tilemap REGULAR_EXPRESSION "src/tilemap/*")
source_group(utilities REGULAR_EXPRESSION "src/utilities/*")

# copy resource files to output binary
# this is only for testing.
file(COPY res DESTINATION ${CMAKE_BINARY_DIR})

# set start up project for visual studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Milk)