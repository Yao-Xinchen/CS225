project(lab_avl)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/tests)

set(SOURCES
#        avltree.cpp
#        avltree_given.cpp
        coloredout.cpp
) # avltree.cpp and avltree_given.cpp are included by headers

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

add_executable(${PROJECT_NAME}_test tests/basic.cpp ${SOURCES})