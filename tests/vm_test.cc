#include "fzlvm/instruction.h"
#include "fzlvm/vm.h"

#include <cstddef>
#include <vector>

#include <gtest/gtest.h>

TEST(VM, EmptyRegistersInitially) {
    fzlvm::VM testVM{};
    EXPECT_EQ(testVM.GetRegister(0), 0);
}

TEST(VM, ExecLoopTerminating) {
    fzlvm::VM testVM{};
    std::vector<std::byte> testROM({std::byte(1), std::byte(3), std::byte(0)});
    testVM.LoadRom(testROM);

    testVM.Exec();
}
