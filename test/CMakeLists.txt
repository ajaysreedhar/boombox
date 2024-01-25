find_package(SDL2 REQUIRED)

set(BASEPATH "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dist/test")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dist/test")

# ---
# Testing pipewire input
# -
# Executable: pipewire-client
# =========================================================================
add_executable(pipewire-client test_pipewire.cpp)
target_link_libraries(pipewire-client PRIVATE x-platform x-input)
target_include_directories(pipewire-client PRIVATE "${CMAKE_SOURCE_DIR}/src")
