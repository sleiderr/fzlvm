#include "fzlvm/vm.h"

#include <gtest/gtest.h>

TEST(ISA, LoadInstruction) {
    fzlvm::VM testVM{};
    std::vector<std::byte> testROM(
        {std::byte(4), std::byte(4), std::byte(0), std::byte(64)});
    testVM.LoadRom(testROM);

    testVM.Step();
    EXPECT_EQ(testVM.GetRegister(4), 64);
}

TEST(ISA, AddInstruction) {
    fzlvm::VM testVM{};
    std::vector<std::byte> testROM(
        {std::byte(1), std::byte(0), std::byte(1), std::byte(2)});
    testVM.LoadRom(testROM);

    testVM.GetRegister(0) = 1024;
    testVM.GetRegister(1) = 2048;

    testVM.Step();
    EXPECT_EQ(testVM.GetRegister(2), 3072);
}