project(mp3)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cs225)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cs225/lodepng)

file(GLOB SOURCES "cs225/*.cpp" "cs225/lodepng/*.cpp" "main.cpp")

add_executable(mp3 ${SOURCES})

file(GLOB TEST_SOURCES "tests/*.cpp")
list(REMOVE_ITEM TEST_SOURCES "main.cpp")

add_executable(mp3_test ${TEST_SOURCES})
target_link_libraries(mp3_test pthread)