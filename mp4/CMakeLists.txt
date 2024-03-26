project(mp4)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories(${PROJECT_SOURCE_DIR})

file(GLOB SOURCES_COLOR "${PROJECT_SOURCE_DIR}/colorPicker/*.cpp")
file(GLOB SOURCES_IMAGE "${PROJECT_SOURCE_DIR}/imageTraversal/*.cpp")
file(GLOB SOURCES_PNG "${PROJECT_SOURCE_DIR}/cs225/*.cpp" "${PROJECT_SOURCE_DIR}/cs225/lodepng/*.cpp")
file(GLOB SOURCES_TEST "${PROJECT_SOURCE_DIR}/tests/*.cpp")
set(SOURCES_MP4 Animation.cpp FloodFilledImage.cpp Point.cpp)

add_executable(${PROJECT_NAME} ${SOURCES_COLOR} ${SOURCES_IMAGE} ${SOURCES_PNG} ${SOURCES_MP4} main.cpp)
add_executable(${PROJECT_NAME}_test ${SOURCES_COLOR} ${SOURCES_IMAGE} ${SOURCES_PNG} ${SOURCES_MP4} ${SOURCES_TEST})