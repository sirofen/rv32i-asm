message(STATUS "Adding ${PROJECT_NAME} tests")

file(GLOB_RECURSE TEST_SRCS test_*.cpp)

add_executable(${PROJECT_NAME}-unittests ${TEST_SRCS})

target_link_libraries(${PROJECT_NAME}-unittests PUBLIC ${PROJECT_NAME}-library
                                                       gtest gtest_main)

# test files
set(ASM_FILE_TEST "${CMAKE_SOURCE_DIR}/tests/bin/uart_test.asm")
set(BIN_FILE_TEST "${CMAKE_SOURCE_DIR}/tests/bin/uart_test.bin")

target_compile_definitions(
  ${PROJECT_NAME}-unittests PRIVATE ASM_FILE_TEST="${ASM_FILE_TEST}"
                                    BIN_FILE_TEST="${BIN_FILE_TEST}")
