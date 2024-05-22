#include "fzlvm/handlers/alu.h"

#include <cstdint>

#include "fzlvm/instruction.h"
#include "fzlvm/vm.h"

namespace fzlvm::handlers::alu {
void AddHandler(fzlvm::instruction::Instruction instruction, fzlvm::VM &vm) {
    auto bytecode = instruction.GetBytecode();
    if (instruction.IsSourceMem() || instruction.IsDestMem()) {
        return;
    }

    auto operandA = static_cast<size_t>(bytecode[1]);

    if (instruction.IsImmediate()) {
        std::uint16_t operandB = static_cast<short>(bytecode[2]) |
                                 (static_cast<short>(bytecode[3]) << 8);

        vm.GetRegister(operandA) += operandB;
    } else {
        auto operandB = static_cast<size_t>(bytecode[2]);

        vm.GetRegister(operandA) += vm.GetRegister(operandB);
    }
}

void SubHandler(instruction::Instruction instruction, VM &vm) {
    auto bytecode = instruction.GetBytecode();

    if (instruction.IsSourceMem() || instruction.IsDestMem()) {
        return;
    }

    auto operandA = static_cast<size_t>(bytecode[1]);

    if (instruction.IsImmediate()) {
        std::uint16_t operandB = static_cast<short>(bytecode[2]) |
                                 (static_cast<short>(bytecode[3]) << 8);

        vm.GetRegister(operandA) -= operandB;
    } else {
        auto operandB = static_cast<size_t>(bytecode[2]);

        vm.GetRegister(operandA) -= vm.GetRegister(operandB);
    }
}

void NotHandler(instruction::Instruction instruction, VM &vm) {}
} // namespace fzlvm::handlers::alu
