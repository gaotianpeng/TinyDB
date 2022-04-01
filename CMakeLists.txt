cmake_minimum_required(VERSION 3.14)
project(TinyDB)
add_subdirectory(src)
enable_testing()

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)