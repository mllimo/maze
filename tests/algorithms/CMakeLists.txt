add_executable(MazeTest
    maze_test.cpp
)

target_link_libraries(MazeTest
    algorithms
    gtest::gtest
)

add_test(NAME MazeTest COMMAND MazeTest)

install(TARGETS MazeTest DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)