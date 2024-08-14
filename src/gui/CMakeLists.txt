find_package(raylib CONFIG REQUIRED)

file(GLOB SOURCES "*.cpp" "*.hpp")

include_directories(..)

add_library(gui ${SOURCES})
target_link_libraries(gui raylib)
target_include_directories(gui PUBLIC ..)