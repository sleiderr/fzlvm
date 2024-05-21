#ifndef FZLVM_INSTRUCTION_H_
#define FZLVM_INSTRUCTION_H_

#include <cstddef>
#include <type_traits>

namespace fzlvm::instruction {
enum class InstructionCode : std::underlying_type_t<std::byte> {
    kAdd,
    kOr,
    kShr,
    kShl,
    kXor,
    kAnd,
    kSub,
    kMov,
    kNot,
    kCmp,
    kHlt
};

struct Opcode {
    std::byte imm : 1;
    std::byte instruction_code : 5;
    std::byte source : 1;
    std::byte destination : 1;
};

class Instruction {
  public:
    Instruction(Opcode opcode) : opcode_{opcode} {}
    Instruction(std::byte opcode) : opcode_{static_cast<Opcode>(opcode)} {};

    Opcode &GetOpcode() { return opcode_; }
    InstructionCode GetInstructionCode() {
        return static_cast<InstructionCode>(opcode_.instruction_code);
    }

  private:
    Opcode opcode_;
};

} // namespace fzlvm::instruction

#endif
