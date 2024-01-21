project(CS225)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cs225)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cs225/lodepng)

add_executable(lab_debug
        main.cpp sketchify.cpp cs225/PNG.cpp cs225/HSLAPixel.cpp cs225/lodepng/lodepng.cpp)
target_include_directories(lab_debug PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(lab_debug_test
        tests/unit_tests.cpp sketchify.cpp cs225/PNG.cpp cs225/HSLAPixel.cpp cs225/lodepng/lodepng.cpp)
target_include_directories(lab_debug_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})