project(lab_ml)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories(${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/tests
)

add_executable(${PROJECT_NAME} main.cpp #[[lab_graphs_random.cpp]] graph.cpp NimLearner.cpp)
add_executable(${PROJECT_NAME}_tests tests/basic.cpp #[[lab_graphs_random.cpp]] graph.cpp NimLearner.cpp)