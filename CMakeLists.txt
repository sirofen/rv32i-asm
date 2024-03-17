cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(rv32i-assembler CXX)

option(BUILD_TESTS "Build tests" ON)

find_package(Boost 1.71 REQUIRED system)
find_package(fmt REQUIRED)

include(FetchContent)

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG        v1.13.0
)

FetchContent_MakeAvailable(spdlog)

file(GLOB_RECURSE SRC_FILES src/assembler/*.cpp)

add_library(rv32i-assembler-library STATIC ${SRC_FILES})
target_compile_options(rv32i-assembler-library PUBLIC -Werror)
target_include_directories(rv32i-assembler-library PUBLIC include)
target_link_libraries(rv32i-assembler-library ${Boost_LIBRARIES} fmt::fmt-header-only spdlog)

add_executable(rv32i-assembler src/main.cpp)
target_link_libraries(rv32i-assembler rv32i-assembler-library)

if (BUILD_TESTS)
  add_subdirectory(tests)
endif()