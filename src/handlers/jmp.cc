#include "fzlvm/handlers/jmp.h"
#include <iostream>

namespace fzlvm::handlers {
void JmpHandler(fzlvm::instruction::Instruction instruction, fzlvm::VM &vm) {
    if (instruction.IsDestMem()) {
        return;
    }

    bool rel_jump = instruction.IsSourceMem();
    auto bytecode = instruction.GetBytecode();
    JmpConditions condition_encoding =
        static_cast<JmpConditions>(static_cast<size_t>(bytecode[1]) & 0b111);

    auto &flags = vm.SysFlags();

    switch (condition_encoding) {
    case JmpConditions::kZero:
        if (!flags.ZeroFlag()) {
            return;
        }
        break;
    case JmpConditions::kNonZero:
        if (flags.ZeroFlag()) {
            return;
        }
        break;
    case JmpConditions::kGreater:
        if (flags.NegativeFlag()) {
            return;
        }
        break;
    case JmpConditions::kLesser:
        if (!flags.NegativeFlag()) {
            return;
        }
        break;
    case JmpConditions::kCarry:
        if (!flags.CarryFlag()) {
            return;
        }
        break;
    case JmpConditions::kNoCarry:
        if (flags.CarryFlag()) {
            return;
        }
        break;
    case JmpConditions::kOverflow:
        if (!flags.OverflowFlag()) {
            return;
        }
        break;
    default:
        break;
    }

    unsigned int addr;
    if (instruction.IsImmediate()) {
        addr = (static_cast<unsigned int>(bytecode[1]) >> 3) |
               static_cast<unsigned int>(bytecode[2]) << 5 |
               static_cast<unsigned int>(bytecode[3]) << 13;
    } else {
        auto reg = static_cast<size_t>(bytecode[2]);
        addr = vm.GetRegister(reg);
    }

    size_t &program_counter = vm.GetProgramCounter();

    if ((!rel_jump && addr > vm.MaxRomAddress()) ||
        (rel_jump && (addr + program_counter) > vm.MaxRomAddress())) {
        std::cerr << "Attempted jump outside of ROM limits. \n";
        return;
    }

    if (rel_jump) {
        program_counter += addr;
    } else {
        program_counter = addr;
    }
}
} // namespace fzlvm::handlers