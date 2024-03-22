project(mp3)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cs225)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cs225/lodepng)

set(SOURCES
        cs225/lodepng/lodepng.cpp
        cs225/PNG.cpp
        cs225/HSLAPixel.cpp
)
add_executable(mp3 main.cpp ${SOURCES})

file(GLOB TEST_SOURCES "tests/*.cpp")

add_executable(mp3_test ${SOURCES} ${TEST_SOURCES})