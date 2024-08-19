cmake_minimum_required(VERSION 3.15)
project(Maze CXX)

set(CMAKE_CXX_STANDARD 20)

option(MAZE_TESTS "Enable Maze tests" OFF)
option(BUILD_SHARED_LIB "Build shared library" OFF)

add_subdirectory(src)

if (${MAZE_TESTS})
    add_subdirectory(tests)
endif()