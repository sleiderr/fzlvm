cmake_minimum_required(VERSION 3.14)
project(fzlvm)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

include_directories(include)

set(FZLVM_SRCS
"include/fzlvm/vm.h"
)

set(FZLVM_Tests
${FZLVM_SRCS}
tests/vm_test.cc
)

enable_testing()

add_executable(
    fzlvmtests
    ${FZLVM_Tests}
)
target_link_libraries(
    fzlvmtests
    GTest::gtest_main
)
target_include_directories(
    fzlvmtests
    PUBLIC
    ${FZLM_SRCS}
)

include(GoogleTest)
gtest_discover_tests(fzlvmtests)