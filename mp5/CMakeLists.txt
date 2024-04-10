project(mp5)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories(${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/cs225
        ${PROJECT_SOURCE_DIR}/tests
        ${PROJECT_SOURCE_DIR}/util
)

file(GLOB UTIL "${PROJECT_SOURCE_DIR}/util/*.cpp")
file(GLOB CS225 "${PROJECT_SOURCE_DIR}/cs225/*.cpp"
        "${PROJECT_SOURCE_DIR}/cs225/lodepng/*.cpp")
file(GLOB TESTS "${PROJECT_SOURCE_DIR}/tests/*.cpp"
        "${PROJECT_SOURCE_DIR}/cs225/catch/catchmain.cpp")

set(SOURCES
#        kdtree.cpp
#        kdtree_extras.cpp
        maptiles.cpp
        mosaiccanvas.cpp
#        point.cpp
        sourceimage.cpp
        tileimage.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${UTIL} ${CS225} main.cpp)
add_executable(${PROJECT_NAME}_tests ${SOURCES} ${UTIL} ${CS225} ${TESTS})