project(lab_graphs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories(${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/images
        ${PROJECT_SOURCE_DIR}/tests
)

add_executable(${PROJECT_NAME} tests.cpp graph.cpp graph_tools.cpp dsets.cpp)
add_executable(${PROJECT_NAME}_demo graph.cpp demo.cpp)
add_executable(${PROJECT_NAME}_test tests/basic.cpp graph.cpp graph_tools.cpp dsets.cpp)