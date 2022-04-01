
set(CMAKE_CXX_STANDARD 11)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_executable(
  hello_test
  hello_test.cc
  hello_mock.cc
)

target_link_libraries(hello_test gtest)
