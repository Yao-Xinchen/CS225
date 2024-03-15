project(lab_quacks)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
        exercises.cpp
        quackfun.cpp
)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

# Add a target for the tests
set(TEST_SOURCES
        tests/basic.cpp
)

add_executable(${PROJECT_NAME}_test ${TEST_SOURCES} ${SOURCES})