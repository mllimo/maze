find_package(raylib CONFIG REQUIRED)

file(GLOB SOURCES "*.cpp" "*.hpp")

include_directories(..)

add_executable(Maze ${SOURCES})
target_link_libraries(Maze algorithms gui raylib)
target_include_directories(Maze PUBLIC ..)

install(TARGETS Maze DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )