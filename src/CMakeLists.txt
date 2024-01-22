find_package(SDL2 REQUIRED)

set(BASEPATH "${CMAKE_SOURCE_DIR}/src")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dist")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dist/lib")

add_definitions(-DBMX_MODE_DEBUG=1)
