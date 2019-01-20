cmake_minimum_required(VERSION 3.6.1)

project(milkengine)

# we're a c++14 family.
set(CMAKE_CXX_STANDARD 14)

# set the ~/cmake module path for project
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

#---------------------------------------------------------------------------
# On windows, you have to point cmake to our third party dependencies.
#---------------------------------------------------------------------------
if (WIN32)

    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

        # provide paths for winGW development libs
        # set(SDL2_PATH ...)
        # set(SDL2_IMAGE_PATH ...)

    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

        # provide paths for visual c++ development libs
        # set(SDL2_PATH ...)
        # set(SDL2_IMAGE_PATH ...)

    endif()
endif()

#---------------------------------------------------------------------------
# run find scripts
#---------------------------------------------------------------------------
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(Lua53 REQUIRED)

#---------------------------------------------------------------------------
# code coverage configuration (ccc)
#---------------------------------------------------------------------------
option(CODE_COVERAGE "Enable coverage reporting" OFF)

add_library(coverage_config INTERFACE)

if(CODE_COVERAGE)
    # Add required flags (GCC & LLVM/Clang)
    target_compile_options(coverage_config INTERFACE
            -O0        # no optimization
            -g         # generate debug info
            --coverage # sets all required flags
            )

    target_link_libraries(coverage_config INTERFACE --coverage)
endif()

#---------------------------------------------------------------------------
# enable testing up in this mafk
#---------------------------------------------------------------------------
include(CTest)
enable_testing()

# create milk lib
add_subdirectory(src)
#create milk exe
add_subdirectory(main)
# create test exe
add_subdirectory(test)

#---------------------------------------------------------------------------
# set start up project for visual studio
#---------------------------------------------------------------------------
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT milkengine)