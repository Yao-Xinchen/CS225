project(lab_btree)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/tests)

set(SOURCES
#        btree.cpp
#        btree_given.cpp
)

add_executable(${PROJECT_NAME} test_btree.cpp ${SOURCES}) # test_btree
add_executable(${PROJECT_NAME}_test tests/basic.cpp ${SOURCES}) # test
add_executable(${PROJECT_NAME}_dict_racer dict_racer.cpp ${SOURCES}) # test2