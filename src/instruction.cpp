#include "fzlvm/instruction.h"

#include <array>
#include <cstdint>

std::array<std::byte, 4> fzlvm::instruction::Instruction::BuildInstruction(
    InstructionCode instruction_code, std::array<std::byte, 3> extra_bytecode,
    bool is_immediate, bool is_source_mem, bool is_dest_mem) {
    auto instruction = std::array<std::byte, 4>();

    auto opcode = (static_cast<std::uint8_t>(instruction_code) << 2);

    if (is_immediate) {
        opcode |= (1 << 7);
    }

    if (is_dest_mem) {
        opcode |= 2;
    }

    if (is_source_mem) {
        opcode |= 1;
    }

    instruction[0] = static_cast<std::byte>(opcode);
    instruction[1] = extra_bytecode[0];
    instruction[2] = extra_bytecode[1];
    instruction[3] = extra_bytecode[2];

    return instruction;
}