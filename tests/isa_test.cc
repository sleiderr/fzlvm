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

TEST(ISA, AddInstructionOverflow) {
    auto addInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kAdd,
        std::array<std::byte, 3>({std::byte(0), std::byte(1), std::byte(0)}));

    auto testVM = SingleInstructionVMBuilder(addInstr);

    testVM.GetRegister(0) = 0xFFFFFFF0;
    testVM.GetRegister(1) = 0xF0;

    testVM.Step();
    EXPECT_TRUE(testVM.SysFlags().OverflowFlag());
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

TEST(ISA, NotInstruction) {
    auto notInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kNot,
        std::array<std::byte, 3>({std::byte(0), std::byte(0), std::byte(0)}));

    auto testVM = SingleInstructionVMBuilder(notInstr);

    testVM.GetRegister(0) = 0xFFFF0000;
    testVM.Step();

    EXPECT_EQ(testVM.GetRegister(0), 0xFFFF);
}

TEST(ISA, AndInstruction) {
    auto andInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kAnd,
        std::array<std::byte, 3>({std::byte(0), std::byte(1), std::byte(0)}));

    auto testVM = SingleInstructionVMBuilder(andInstr);

    testVM.GetRegister(0) = 0x7;
    testVM.GetRegister(1) = 0x13;
    testVM.Step();

    EXPECT_EQ(testVM.GetRegister(0), 0x3);
}

TEST(ISA, AndInstructionImm) {
    auto andInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kAnd,
        std::array<std::byte, 3>({std::byte(0), std::byte(0x13), std::byte(0)}),
        true);

    auto testVM = SingleInstructionVMBuilder(andInstr);

    testVM.GetRegister(0) = 0x7;
    testVM.Step();

    EXPECT_EQ(testVM.GetRegister(0), 0x3);
}

TEST(ISA, OrInstruction) {
    auto orInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kOr,
        std::array<std::byte, 3>({std::byte(0), std::byte(1), std::byte(0)}));

    auto testVM = SingleInstructionVMBuilder(orInstr);

    testVM.GetRegister(0) = 0x7;
    testVM.GetRegister(1) = 0x13;
    testVM.Step();

    EXPECT_EQ(testVM.GetRegister(0), 0x17);
}

TEST(ISA, OrInstructionImm) {
    auto orInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kOr,
        std::array<std::byte, 3>({std::byte(0), std::byte(0x13), std::byte(0)}),
        true);

    auto testVM = SingleInstructionVMBuilder(orInstr);

    testVM.GetRegister(0) = 0x7;
    testVM.Step();

    EXPECT_EQ(testVM.GetRegister(0), 0x17);
}

TEST(ISA, XorInstruction) {
    auto xorInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kXor,
        std::array<std::byte, 3>({std::byte(0), std::byte(1), std::byte(0)}));

    auto testVM = SingleInstructionVMBuilder(xorInstr);

    testVM.GetRegister(0) = 0x7;
    testVM.GetRegister(1) = 0x13;
    testVM.Step();

    EXPECT_EQ(testVM.GetRegister(0), 0x14);
}

TEST(ISA, XorInstructionImm) {
    auto xorInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kXor,
        std::array<std::byte, 3>({std::byte(0), std::byte(0x13), std::byte(0)}),
        true);

    auto testVM = SingleInstructionVMBuilder(xorInstr);

    testVM.GetRegister(0) = 0x7;
    testVM.Step();

    EXPECT_EQ(testVM.GetRegister(0), 0x14);
}

TEST(ISA, ShlInstruction) {
    auto shlInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kShl,
        std::array<std::byte, 3>({std::byte(0), std::byte(1), std::byte(0)}));

    auto testVM = SingleInstructionVMBuilder(shlInstr);

    testVM.GetRegister(0) = 0x1;
    testVM.GetRegister(1) = 0x8;
    testVM.Step();

    EXPECT_EQ(testVM.GetRegister(0), 0x100);
}

TEST(ISA, ShlInstructionImm) {
    auto shlInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kShl,
        std::array<std::byte, 3>({std::byte(0), std::byte(0x8), std::byte(0)}),
        true);

    auto testVM = SingleInstructionVMBuilder(shlInstr);

    testVM.GetRegister(0) = 0x1;
    testVM.Step();

    EXPECT_EQ(testVM.GetRegister(0), 0x100);
}

TEST(ISA, ShrInstruction) {
    auto shrInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kShr,
        std::array<std::byte, 3>({std::byte(0), std::byte(1), std::byte(0)}));

    auto testVM = SingleInstructionVMBuilder(shrInstr);

    testVM.GetRegister(0) = 0x100;
    testVM.GetRegister(1) = 0x8;
    testVM.Step();

    EXPECT_EQ(testVM.GetRegister(0), 0x1);
}

TEST(ISA, ShrInstructionImm) {
    auto shrInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kShr,
        std::array<std::byte, 3>({std::byte(0), std::byte(0x8), std::byte(0)}),
        true);

    auto testVM = SingleInstructionVMBuilder(shrInstr);

    testVM.GetRegister(0) = 0x100;
    testVM.Step();

    EXPECT_EQ(testVM.GetRegister(0), 0x1);
}

TEST(ISA, CmpInstructionEq) {
    auto cmpInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kCmp,
        std::array<std::byte, 3>({std::byte(0), std::byte(1), std::byte(0)}));

    auto testVM = SingleInstructionVMBuilder(cmpInstr);

    testVM.GetRegister(0) = 0x100;
    testVM.GetRegister(1) = 0x100;
    testVM.Step();

    EXPECT_TRUE(testVM.SysFlags().ZeroFlag());
}

TEST(ISA, CmpInstructionNeqLeq) {
    auto cmpInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kCmp,
        std::array<std::byte, 3>({std::byte(0), std::byte(1), std::byte(0)}));

    auto testVM = SingleInstructionVMBuilder(cmpInstr);

    testVM.GetRegister(0) = 0x0;
    testVM.GetRegister(1) = 0x100;
    testVM.Step();

    EXPECT_FALSE(testVM.SysFlags().ZeroFlag());
    EXPECT_TRUE(testVM.SysFlags().NegativeFlag());
    EXPECT_TRUE(testVM.SysFlags().OverflowFlag());
}

TEST(ISA, CmpInstructionEqImm) {
    auto cmpInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kCmp,
        std::array<std::byte, 3>({std::byte(0), std::byte(0), std::byte(0x1)}),
        true);

    auto testVM = SingleInstructionVMBuilder(cmpInstr);

    testVM.GetRegister(0) = 0x100;
    testVM.Step();

    EXPECT_TRUE(testVM.SysFlags().ZeroFlag());
}

TEST(ISA, CmpInstructionNeqGeqImm) {
    auto cmpInstr = fzlvm::instruction::Instruction::BuildInstruction(
        fzlvm::instruction::InstructionCode::kCmp,
        std::array<std::byte, 3>({std::byte(0), std::byte(0x10), std::byte(0)}),
        true);

    auto testVM = SingleInstructionVMBuilder(cmpInstr);

    testVM.GetRegister(0) = 0x100;
    testVM.Step();

    EXPECT_FALSE(testVM.SysFlags().ZeroFlag());
    EXPECT_FALSE(testVM.SysFlags().NegativeFlag());
    EXPECT_FALSE(testVM.SysFlags().OverflowFlag());
}