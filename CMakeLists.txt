cmake_minimum_required(VERSION 3.10)
project(CS225)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -g -O0 -Wall -Wextra -pedantic")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -std=c++1y -lpng -lpthread -lm")

set(SUBDIR
        lab_intro
        lab_debug
        lab_inheritance
        lab_gdb2
        mp1
        mp2
)

foreach (subdir ${SUBDIR})
    add_subdirectory(${subdir})
endforeach ()