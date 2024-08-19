find_package(raylib CONFIG REQUIRED)

file(GLOB SOURCES "*.cpp" "*.hpp")

include_directories(..)

if(BUILD_SHARED_LIB)
    add_library(algorithms SHARED ${SOURCES})
else()
    add_library(algorithms STATIC ${SOURCES})
endif()

set_target_properties(algorithms PROPERTIES OUTPUT_NAME "algorithms")
target_link_libraries(algorithms raylib)
target_include_directories(algorithms PUBLIC ..)

install(TARGETS algorithms
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)