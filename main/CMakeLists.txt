project(milkexe)

add_executable(milk main.cpp)

# link lib files
target_link_libraries(milk milklib)

# copy resource files to output binary
# this is only for testing.
file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${milkexe_BINARY_DIR})