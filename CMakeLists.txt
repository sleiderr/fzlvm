cmake_minimum_required(VERSION 3.14)
project(fzlvm)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

include_directories(include)

set(FZLVM_HEADERS
"include/fzlvm/vm.h"
"include/fzlvm/instruction.h"
"include/fzlvm/registers/sysflags.h"
"include/fzlvm/handlers/alu.h"
"include/fzlvm/handlers/mem.h"
"include/fzlvm/handlers/jmp.h"
"include/fzlvm/handlers/handlers.h"
)

set(FZLVM_SRCS
${FZLVM_HEADERS}
"src/vm.cc"
"src/instruction.cc"
"src/handlers/alu.cc"
"src/handlers/jmp.cc"
)

set(FZLVM_REPL_SRCS
${FZLVM_SRCS}
"src/repl/main.cc"
"src/repl/utils.cc"
)

set(FZLVM_Tests
${FZLVM_SRCS}
"tests/vm_test.cc"
"tests/isa_test.cc"
"tests/jmp_test.cc"
)

add_executable(
    fzlvm
    ${FZLVM_REPL_SRCS}
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