cmake_minimum_required(VERSION 3.10)
project(CS225)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -Wall -Wextra -pedantic") # remove -O3 for debugging
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lpng -lpthread -lm")

set(SUBDIR
        lab_intro
        lab_debug
        lab_inheritance
        lab_gdb2
        lab_quacks
        lab_trees
        lab_huffman
        lab_avl
        lab_btree
        lab_hash
        lab_heaps
        lab_dict
        lab_graphs
        lab_ml
        mp1
        mp2
        mp3
        mp4
        mp5
        mp6
        mp7
)

foreach (subdir ${SUBDIR})
    add_subdirectory(${subdir})
endforeach ()