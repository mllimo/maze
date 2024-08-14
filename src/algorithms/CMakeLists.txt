find_package(raylib CONFIG REQUIRED)

file(GLOB SOURCES "*.cpp" "*.hpp")

include_directories(..)

add_library(algorithms ${SOURCES})
target_link_libraries(algorithms raylib)
target_include_directories(algorithms PUBLIC ..)