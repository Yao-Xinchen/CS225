project(lab_inheritance)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -g -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-delete-non-virtual-dtor")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cs225)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cs225/lodepng)

set(PROVIDED_SRCS
        cs225/PNG.cpp cs225/lodepng/lodepng.cpp cs225/HSLAPixel.cpp vector2.cpp line.cpp)

add_executable(lab_inheritance
        ${PROVIDED_SRCS} main.cpp shape.cpp rectangle.cpp)
add_executable(lab_inh_test_virtual
        ${PROVIDED_SRCS} test_virtual.cpp shape.cpp rectangle.cpp)
add_executable(lab_inh_test_pure_virtual
        ${PROVIDED_SRCS} test_pure_virtual.cpp shape.cpp rectangle.cpp circle.cpp truck.cpp)
add_executable(lab_inh_test_destructor
        ${PROVIDED_SRCS} test_destructor.cpp shape.cpp triangle.cpp)
add_executable(lab_inh_test_slicing
        ${PROVIDED_SRCS} test_slicing.cpp shape.cpp rectangle.cpp circle.cpp flower.cpp triangle.cpp)
add_executable(lab_inh_test_constructor
        ${PROVIDED_SRCS} test_constructor.cpp shape.cpp circle.cpp)
add_executable(lab_inheritance_test
        ${PROVIDED_SRCS} tests/basic.cpp shape.cpp rectangle.cpp triangle.cpp circle.cpp truck.cpp flower.cpp line.cpp vector2.cpp line.cpp vector2.cpp)