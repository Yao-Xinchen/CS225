project(lab_heaps)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories(${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/tests)

add_executable(${PROJECT_NAME} testheap.cpp coloredout.cpp)
add_executable(${PROJECT_NAME}_test tests/basic.cpp coloredout.cpp)
