#include "fzlvm/instruction.h"
#include "fzlvm/vm.h"

#include <gtest/gtest.h>

fzlvm::VM SingleInstructionVMBuilder(std::array<std::byte, 4> instruction) {
    fzlvm::VM testVM{};
    std::vector<std::byte> testROM{};
    testROM.insert(testROM.end(), instruction.begin(), instruction.end());

    testVM.LoadRom(std::move(testROM));

    return testVM;
}

TEST(ISA, AddInstruction) {
    auto addInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kAdd,
        std::array<std::byte, 3>({std::byte(0), std::byte(1), std::byte(0)}));

    auto testVM = SingleInstructionVMBuilder(addInstr);

    testVM.GetRegister(0) = 1024;
    testVM.GetRegister(1) = 2048;

    testVM.Step();
    EXPECT_EQ(testVM.GetRegister(0), 3072);
}

TEST(ISA, AddInstructionImm) {
    auto addInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kAdd,
        std::array<std::byte, 3>({std::byte(0), std::byte(64), std::byte(0)}),
        true);

    auto testVM = SingleInstructionVMBuilder(addInstr);

    testVM.Step();

    EXPECT_EQ(testVM.GetRegister(0), 64);
}

TEST(ISA, SubInstruction) {
    auto subInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kSub,
        std::array<std::byte, 3>({std::byte(0), std::byte(1), std::byte(0)}));

    auto testVM = SingleInstructionVMBuilder(subInstr);

    testVM.GetRegister(0) = 128;
    testVM.GetRegister(1) = 60;
    testVM.Step();

    EXPECT_EQ(testVM.GetRegister(0), 68);
}

TEST(ISA, SubInstructionImm) {
    auto subInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kSub,
        std::array<std::byte, 3>({std::byte(0), std::byte(64), std::byte(0)}),
        true);

    auto testVM = SingleInstructionVMBuilder(subInstr);

    testVM.GetRegister(0) = 128;
    testVM.Step();

    EXPECT_EQ(testVM.GetRegister(0), 64);
}
