find_package(SDL2 REQUIRED)

set(BASEPATH "${CMAKE_SOURCE_DIR}/src")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dist")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dist/lib")

add_definitions(-DBMX_MODE_DEBUG=1)

add_library(x-platform SHARED
    platform/logger.cpp         platform/logger.hpp
    platform/filesystem.cpp     platform/filesystem.hpp)

add_library(x-display SHARED
    ui/except.cpp           ui/except.hpp
    ui/assert.hpp
    ui/sprite_material.cpp  ui/sprite_material.hpp
    ui/renderer.hpp         ui/renderer.cpp
    ui/display_context.cpp  ui/display_context.hpp)
target_link_libraries(x-display PUBLIC -lSDL2 -lSDL2_image x-platform)
target_include_directories(x-display PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(boombox main.cpp)
target_link_libraries(boombox PRIVATE x-platform x-display)
target_include_directories(boombox PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
