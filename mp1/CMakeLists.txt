set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -g -O0 -Wall -Wextra -pedantic")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cs225)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cs225/lodepng)

add_executable(mp1
        main.cpp mp1.cpp cs225/PNG.cpp cs225/HSLAPixel.cpp cs225/lodepng/lodepng.cpp)
target_include_directories(mp1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(mp1_test
        tests/unit_tests.cpp mp1.cpp cs225/PNG.cpp cs225/HSLAPixel.cpp cs225/lodepng/lodepng.cpp)
target_include_directories(mp1_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})