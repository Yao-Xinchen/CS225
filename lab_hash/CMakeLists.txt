project(lab_hash)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

file(GLOB TESTS "${PROJECT_SOURCE_DIR}/tests/*.cpp")

add_executable(${PROJECT_NAME}_charcount
        hashes.cpp textfile.cpp
        charcount.cpp)

add_executable(${PROJECT_NAME}_wordcount
        hashes.cpp textfile.cpp
        wordcount.cpp)

add_executable(${PROJECT_NAME}_anagramtest
        hashes.cpp textfile.cpp
        anagramtest.cpp)

add_executable(${PROJECT_NAME}_genlog
        logfile_generator.cpp)

add_executable(${PROJECT_NAME}_lfparse
        logfile_parser.cpp lfparse.cpp hashes.cpp)

add_executable(${PROJECT_NAME}_test
        ${TESTS} hashes.cpp textfile.cpp)