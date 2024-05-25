#ifndef FZLVM_INSTRUCTION_H_
#define FZLVM_INSTRUCTION_H_

#include <cstddef>
#include <cstdint>
#include <span>

namespace fzlvm::instruction {
enum class InstructionCode : std::uint8_t {
    kNop,
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
    kHlt,
    kJmp
};

class Instruction {
  public:
    Instruction(std::span<std::byte, 4> instruction_bytecode)
        : bytecode_{instruction_bytecode} {};

    static std::array<std::byte, 4>
    BuildInstruction(InstructionCode, std::array<std::byte, 3> extra_bytecode,
                     bool is_immediate = false, bool is_source_mem = false,
                     bool is_dest_mem = false);

    constexpr std::byte GetOpcode() const { return bytecode_[0]; }
    constexpr bool IsImmediate() const {
        return static_cast<int>(bytecode_[0]) & (1 << 7);
    }
    constexpr bool IsSourceMem() const {
        return static_cast<int>(bytecode_[0]) & 1;
    }
    constexpr bool IsDestMem() const {
        return static_cast<int>(bytecode_[0]) & 2;
    }
    constexpr InstructionCode GetInstructionCode() const {
        return static_cast<InstructionCode>(
            (static_cast<int>(bytecode_[0]) >> 2) & 0x1F);
    }

    std::span<std::byte, 4> GetBytecode() { return bytecode_; }

  private:
    std::span<std::byte, 4> bytecode_;
};

} // namespace fzlvm::instruction

#endif
