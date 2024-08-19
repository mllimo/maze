find_package(raylib CONFIG REQUIRED)

include_directories(..)

file(GLOB SOURCES "*.cpp" "*.hpp")

if(BUILD_SHARED_LIB)
    add_library(gui SHARED ${SOURCES})
else()
    add_library(gui STATIC ${SOURCES})
endif()

set_target_properties(gui PROPERTIES OUTPUT_NAME "gui")
target_link_libraries(gui raylib)
target_include_directories(gui PUBLIC ..)

install(TARGETS gui
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)