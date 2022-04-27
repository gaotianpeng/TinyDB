add_executable(storage 
    ${CMAKE_CURRENT_SOURCE_DIR}/test/storage_unittest.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/test/main_unittest.cc)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)


target_link_libraries(storage gtest gmock)