
set(CMAKE_CXX_STANDARD 11)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

file(GLOB UT_SRC *.h *.cc)

add_executable(
  hello_test
  ${UT_SRC}
)

target_link_libraries(hello_test gtest gmock)
