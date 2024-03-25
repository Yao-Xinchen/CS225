project(lab_huffman)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Define the source files
set(SOURCES_ENCODER huffman_tree.cpp frequency.cpp encoder.cpp encoder_prog.cpp binary_file_writer.cpp binary_file_reader.cpp)
set(SOURCES_DECODER huffman_tree.cpp frequency.cpp decoder.cpp decoder_prog.cpp binary_file_writer.cpp binary_file_reader.cpp)
set(SOURCES_PRINTER binary_file_reader.cpp print_as_ascii.cpp)
set(SOURCES_TEST frequency.cpp encoder.cpp decoder.cpp binary_file_writer.cpp binary_file_reader.cpp huffman_tree.cpp)

# Add the executable targets
add_executable(${PROJECT_NAME}_encoder ${SOURCES_ENCODER})
add_executable(${PROJECT_NAME}_decoder ${SOURCES_DECODER})
add_executable(${PROJECT_NAME}_print_as_ascii ${SOURCES_PRINTER})
add_executable(${PROJECT_NAME}_test ${SOURCES_TEST} tests/basic.cpp)