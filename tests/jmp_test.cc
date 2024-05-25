#include "fzlvm/instruction.h"

#include <gtest/gtest.h>

#include "fzlvm/vm.h"

fzlvm::VM SingleJmpVMBuilder(std::array<std::byte, 4> jmp_instruction) {
    auto addInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kAdd,
        std::array<std::byte, 3>({std::byte(0), std::byte(64), std::byte(0)}),
        true);

    auto nopInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kNop, std::array<std::byte, 3>());

    fzlvm::VM testVM{};
    std::vector<std::byte> testROM{};

    testROM.insert(testROM.end(), jmp_instruction.begin(),
                   jmp_instruction.end());
    testROM.insert(testROM.end(), addInstr.begin(), addInstr.end());
    testROM.insert(testROM.end(), nopInstr.begin(), nopInstr.end());

    testVM.LoadRom(std::move(testROM));

    return testVM;
}

TEST(ISAJmp, AbsJmpNoCondImm) {
    auto jmpInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kJmp,
        std::array<std::byte, 3>(
            {std::byte(0b01000000), std::byte(0), std::byte(0)}),
        true);

    auto testVM = SingleJmpVMBuilder(jmpInstr);
    testVM.Exec();

    EXPECT_NE(testVM.GetRegister(0), 64);
}

TEST(ISAJmp, AbsJmpNoCondReg) {
    auto jmpInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kJmp,
        std::array<std::byte, 3>(
            {std::byte(0b00000000), std::byte(1), std::byte(0)}),
        false);

    auto testVM = SingleJmpVMBuilder(jmpInstr);
    testVM.GetRegister(1) = 8;
    testVM.Exec();

    EXPECT_NE(testVM.GetRegister(0), 64);
}

TEST(ISAJmp, RelJmpNoCondImm) {
    auto jmpInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kJmp,
        std::array<std::byte, 3>(
            {std::byte(0b00100000), std::byte(0), std::byte(0)}),
        true, true);

    auto testVM = SingleJmpVMBuilder(jmpInstr);
    testVM.Exec();

    EXPECT_NE(testVM.GetRegister(0), 64);
}

TEST(ISAJmp, AbsJmpZeroImm) {
    auto jmpInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kJmp,
        std::array<std::byte, 3>(
            {std::byte(0b01000001), std::byte(0), std::byte(0)}),
        true);

    auto testVM = SingleJmpVMBuilder(jmpInstr);
    testVM.Exec();

    EXPECT_NE(testVM.GetRegister(0), 64);

    jmpInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kJmp,
        std::array<std::byte, 3>(
            {std::byte(0b01000001), std::byte(0), std::byte(0)}),
        true);

    testVM = SingleJmpVMBuilder(jmpInstr);
    testVM.SysFlags().ClearZeroFlag();
    testVM.Exec();

    EXPECT_EQ(testVM.GetRegister(0), 64);
}

TEST(ISAJmp, AbsJmpGeqImm) {
    auto jmpInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kJmp,
        std::array<std::byte, 3>(
            {std::byte(0b01000011), std::byte(0), std::byte(0)}),
        true);

    auto testVM = SingleJmpVMBuilder(jmpInstr);
    testVM.Exec();

    EXPECT_NE(testVM.GetRegister(0), 64);

    jmpInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kJmp,
        std::array<std::byte, 3>(
            {std::byte(0b01000011), std::byte(0), std::byte(0)}),
        true);

    testVM = SingleJmpVMBuilder(jmpInstr);
    testVM.SysFlags().SetNegativeFlag();
    testVM.Exec();

    EXPECT_EQ(testVM.GetRegister(0), 64);
}

TEST(ISAJmp, AbsJmpOverflowImm) {
    auto jmpInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kJmp,
        std::array<std::byte, 3>(
            {std::byte(0b01000111), std::byte(0), std::byte(0)}),
        true);

    auto testVM = SingleJmpVMBuilder(jmpInstr);
    testVM.SysFlags().SetOverflowFlag();
    testVM.Exec();

    EXPECT_NE(testVM.GetRegister(0), 64);

    jmpInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kJmp,
        std::array<std::byte, 3>(
            {std::byte(0b01000111), std::byte(0), std::byte(0)}),
        true);

    testVM = SingleJmpVMBuilder(jmpInstr);
    testVM.Exec();

    EXPECT_EQ(testVM.GetRegister(0), 64);
}