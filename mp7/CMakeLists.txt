project(mp7)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories(${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/cs225
        ${PROJECT_SOURCE_DIR}/cs225/lodepng
        ${PROJECT_SOURCE_DIR}/tests
)

file(GLOB SOURCES_DSETS "dsets.cpp" "testdsets.cpp")
file(GLOB SOURCES_SQUAREMAZE "dsets.cpp" "maze.cpp" "testsquaremaze.cpp" "cs225/*.cpp" "cs225/lodepng/*.cpp")
file(GLOB SOURCES_TESTS "dsets.cpp" "maze.cpp" "cs225/*.cpp" "cs225/lodepng/*.cpp" "tests/*.cpp")

add_executable(${PROJECT_NAME}_dsets ${SOURCES_DSETS})
add_executable(${PROJECT_NAME}_squaremaze ${SOURCES_SQUAREMAZE})
add_executable(${PROJECT_NAME}_test ${SOURCES_TESTS})