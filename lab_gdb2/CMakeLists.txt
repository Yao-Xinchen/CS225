project(lab_gdb2)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -pedantic -Wall -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -fsanitize=address -fno-omit-frame-pointer")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cs225)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cs225/lodepng)

set(SOURCES
        cs225/lodepng/lodepng.cpp
        cs225/HSLAPixel.cpp
        cs225/PNG.cpp
#        cs225/RGB_HSL.cpp
        skipList.cpp
        skipList_given.cpp
        skipNode.cpp
)

add_executable(lab_gdb2 main.cpp ${SOURCES})

file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
add_executable(lab_gdb2_test ${TEST_SOURCES} ${SOURCES})

file(GLOB_RECURSE EXAMPLE_SOURCES "gdb-examples/*.cpp")
foreach (EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)
    add_executable(lab_gdb2_${EXAMPLE_NAME} ${EXAMPLE_SOURCE})
endforeach ()