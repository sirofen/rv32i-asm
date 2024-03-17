message(STATUS "Adding ${PROJECT_NAME} tests")

file(GLOB_RECURSE TEST_SRCS test_*.cpp)

add_executable(${PROJECT_NAME}-unittests ${TEST_SRCS} main.cpp)

target_link_libraries(${PROJECT_NAME}-unittests PUBLIC ${PROJECT_NAME}-library gtest)
