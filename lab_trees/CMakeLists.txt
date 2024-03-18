project(lab_trees)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
#        binarytree.cpp
#        binarytree_given.cpp
        coloredout.cpp
)
# the `binarytree_given.cpp` and `binarytree.cpp` have been included by the header files

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

# Add a target for the tests
set(TEST_SOURCES
        tests/basic.cpp
)

add_executable(${PROJECT_NAME}_test ${TEST_SOURCES} ${SOURCES})