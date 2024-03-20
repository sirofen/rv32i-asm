cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(rv32i-assembler CXX)

option(BUILD_TESTS "Build tests" ON)

find_package(Boost 1.71 REQUIRED system)

include(cmake/ExternalLibraries.cmake)

file(GLOB_RECURSE SRC_FILES src/assembler/*.cpp)

add_library(rv32i-assembler-library STATIC ${SRC_FILES})
target_include_directories(rv32i-assembler-library PUBLIC include)
target_link_libraries(rv32i-assembler-library ${Boost_LIBRARIES}
                      ${EXTERNAL_LIB_TARGETS})

target_compile_options(rv32i-assembler-library PUBLIC -Werror)

add_executable(rv32i-assembler src/main.cpp)
target_link_libraries(rv32i-assembler rv32i-assembler-library)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()
