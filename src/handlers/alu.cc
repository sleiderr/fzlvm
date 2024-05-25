#include "fzlvm/handlers/alu.h"

#include <cstdint>
#include <iostream>

#include "fzlvm/instruction.h"
#include "fzlvm/registers/sysflags.h"
#include "fzlvm/vm.h"

namespace fzlvm::handlers::alu {
void FlagUpdate(fzlvm::VM &vm, size_t operandA) {
    int updated_register = vm.GetRegister(operandA);
    registers::SystemFlags sys_flags = vm.SysFlags();

    if (!updated_register) {
        sys_flags.SetZeroFlag();
    } else {
        sys_flags.ClearZeroFlag();
    }

    if (updated_register & (1 << 31)) {
        sys_flags.SetNegativeFlag();
    } else {
        sys_flags.ClearNegativeFlag();
    }
}

void AddHandler(fzlvm::instruction::Instruction instruction, fzlvm::VM &vm) {
    auto bytecode = instruction.GetBytecode();
    if (instruction.IsSourceMem() || instruction.IsDestMem()) {
        return;
    }

    auto operandA = static_cast<size_t>(bytecode[1]);
    auto &registerA = vm.GetRegister(operandA);

    if (instruction.IsImmediate()) {
        std::uint16_t operandB = static_cast<short>(bytecode[2]) |
                                 (static_cast<short>(bytecode[3]) << 8);

        if (__builtin_add_overflow(registerA, operandB, &registerA)) {
            vm.SysFlags().SetOverflowFlag();
        } else {
            vm.SysFlags().ClearOverflowFlag();
        }
    } else {
        auto operandB = static_cast<size_t>(bytecode[2]);
        if (__builtin_add_overflow(registerA, vm.GetRegister(operandB),
                                   &registerA)) {
            vm.SysFlags().SetOverflowFlag();
        } else {
            vm.SysFlags().ClearOverflowFlag();
        }
    }

    FlagUpdate(vm, operandA);
}

void SubHandler(instruction::Instruction instruction, VM &vm) {
    auto bytecode = instruction.GetBytecode();

    if (instruction.IsSourceMem() || instruction.IsDestMem()) {
        return;
    }

    auto operandA = static_cast<size_t>(bytecode[1]);
    auto &registerA = vm.GetRegister(operandA);

    if (instruction.IsImmediate()) {
        std::uint16_t operandB = static_cast<short>(bytecode[2]) |
                                 (static_cast<short>(bytecode[3]) << 8);

        if (__builtin_sub_overflow(registerA, operandB, &registerA)) {
            vm.SysFlags().SetOverflowFlag();
        } else {
            vm.SysFlags().ClearOverflowFlag();
        }

    } else {
        auto operandB = static_cast<size_t>(bytecode[2]);

        if (__builtin_sub_overflow(registerA, vm.GetRegister(operandB),
                                   &registerA)) {
            vm.SysFlags().SetOverflowFlag();
        } else {
            vm.SysFlags().ClearOverflowFlag();
        }
    }

    FlagUpdate(vm, operandA);
}

void NotHandler(instruction::Instruction instruction, VM &vm) {
    auto bytecode = instruction.GetBytecode();

    auto operandA = static_cast<size_t>(bytecode[1]);

    vm.GetRegister(operandA) = ~vm.GetRegister(operandA);

    FlagUpdate(vm, operandA);
}

void XorHandler(instruction::Instruction instruction, VM &vm) {
    auto bytecode = instruction.GetBytecode();

    if (instruction.IsSourceMem() || instruction.IsDestMem()) {
        return;
    }

    auto operandA = static_cast<size_t>(bytecode[1]);

    if (instruction.IsImmediate()) {
        std::uint16_t operandB = static_cast<short>(bytecode[2]) |
                                 (static_cast<short>(bytecode[3]) << 8);

        vm.GetRegister(operandA) ^= operandB;
    } else {
        auto operandB = static_cast<size_t>(bytecode[2]);

        vm.GetRegister(operandA) ^= vm.GetRegister(operandB);
    }

    FlagUpdate(vm, operandA);
}

void OrHandler(instruction::Instruction instruction, VM &vm) {
    auto bytecode = instruction.GetBytecode();

    if (instruction.IsSourceMem() || instruction.IsDestMem()) {
        return;
    }

    auto operandA = static_cast<size_t>(bytecode[1]);

    if (instruction.IsImmediate()) {
        std::uint16_t operandB = static_cast<short>(bytecode[2]) |
                                 (static_cast<short>(bytecode[3]) << 8);

        vm.GetRegister(operandA) |= operandB;
    } else {
        auto operandB = static_cast<size_t>(bytecode[2]);

        vm.GetRegister(operandA) |= vm.GetRegister(operandB);
    }

    FlagUpdate(vm, operandA);
}

void AndHandler(instruction::Instruction instruction, VM &vm) {
    auto bytecode = instruction.GetBytecode();

    if (instruction.IsSourceMem() || instruction.IsDestMem()) {
        return;
    }

    auto operandA = static_cast<size_t>(bytecode[1]);

    if (instruction.IsImmediate()) {
        std::uint16_t operandB = static_cast<short>(bytecode[2]) |
                                 (static_cast<short>(bytecode[3]) << 8);

        vm.GetRegister(operandA) &= operandB;
    } else {
        auto operandB = static_cast<size_t>(bytecode[2]);

        vm.GetRegister(operandA) &= vm.GetRegister(operandB);
    }

    FlagUpdate(vm, operandA);
}

void ShlHandler(instruction::Instruction instruction, VM &vm) {
    auto bytecode = instruction.GetBytecode();

    if (instruction.IsSourceMem() || instruction.IsDestMem()) {
        return;
    }

    auto operandA = static_cast<size_t>(bytecode[1]);

    if (instruction.IsImmediate()) {
        std::uint16_t operandB = static_cast<short>(bytecode[2]) |
                                 (static_cast<short>(bytecode[3]) << 8);

        vm.GetRegister(operandA) <<= operandB;
    } else {
        auto operandB = static_cast<size_t>(bytecode[2]);

        vm.GetRegister(operandA) <<= vm.GetRegister(operandB);
    }

    FlagUpdate(vm, operandA);
}

void ShrHandler(instruction::Instruction instruction, VM &vm) {
    auto bytecode = instruction.GetBytecode();

    if (instruction.IsSourceMem() || instruction.IsDestMem()) {
        return;
    }

    auto operandA = static_cast<size_t>(bytecode[1]);

    if (instruction.IsImmediate()) {
        std::uint16_t operandB = static_cast<short>(bytecode[2]) |
                                 (static_cast<short>(bytecode[3]) << 8);

        vm.GetRegister(operandA) >>= operandB;
    } else {
        auto operandB = static_cast<size_t>(bytecode[2]);

        vm.GetRegister(operandA) >>= vm.GetRegister(operandB);
    }

    FlagUpdate(vm, operandA);
}

void CmpHandler(instruction::Instruction instruction, VM &vm) {
    auto bytecode = instruction.GetBytecode();

    if (instruction.IsSourceMem() || instruction.IsDestMem()) {
        return;
    }

    auto operandA = static_cast<size_t>(bytecode[1]);
    auto registerA = vm.GetRegister(operandA);
    auto result = new unsigned int;

    if (instruction.IsImmediate()) {
        std::uint16_t operandB = static_cast<short>(bytecode[2]) |
                                 (static_cast<short>(bytecode[3]) << 8);

        if (__builtin_sub_overflow(registerA, operandB, result)) {
            vm.SysFlags().SetOverflowFlag();
        } else {
            vm.SysFlags().ClearOverflowFlag();
        }

    } else {
        auto operandB = static_cast<size_t>(bytecode[2]);

        if (__builtin_sub_overflow(registerA, vm.GetRegister(operandB),
                                   result)) {
            vm.SysFlags().SetOverflowFlag();
        } else {
            vm.SysFlags().ClearOverflowFlag();
        }
    }
    auto &sys_flags = vm.SysFlags();

    if (*result) {
        sys_flags.ClearZeroFlag();
    } else {
        sys_flags.SetZeroFlag();
    }

    if ((*result) & (1 << 31)) {
        sys_flags.SetNegativeFlag();
    } else {
        sys_flags.ClearNegativeFlag();
    }

    delete result;
}

} // namespace fzlvm::handlers::alu
