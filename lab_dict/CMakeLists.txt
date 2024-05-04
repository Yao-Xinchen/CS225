project(lab_dict)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Add the executables
add_executable(${PROJECT_NAME}_anagram_finder anagram_dict.cpp anagram_finder.cpp)
add_executable(${PROJECT_NAME}_fib_generator fib.cpp fib_generator.cpp)
add_executable(${PROJECT_NAME}_fac fac.cpp)
add_executable(${PROJECT_NAME}_homophone_puzzle pronounce_dict.cpp cartalk_puzzle.cpp homophone_puzzle.cpp)
add_executable(${PROJECT_NAME}_find_common_words common_words.cpp find_common_words.cpp)

# Add the test executable
add_executable(${PROJECT_NAME}_test tests/unit_tests.cpp anagram_dict.cpp pronounce_dict.cpp cartalk_puzzle.cpp fib.cpp common_words.cpp )