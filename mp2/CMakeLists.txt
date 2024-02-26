project(mp2)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cs225)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cs225/lodepng)

add_executable(mp2
        main.cpp
        Image.cpp
        StickerSheet.cpp
        cs225/PNG.cpp
        cs225/HSLAPixel.cpp
        cs225/lodepng/lodepng.cpp)

add_executable(mp2-1
        mp2-1.cpp
        Image.cpp
        cs225/PNG.cpp
        cs225/HSLAPixel.cpp
        cs225/lodepng/lodepng.cpp)

add_executable(mp2_test
        tests/unit_tests.cpp
        Image.cpp
        StickerSheet.cpp
        cs225/PNG.cpp
        cs225/HSLAPixel.cpp
        cs225/lodepng/lodepng.cpp)