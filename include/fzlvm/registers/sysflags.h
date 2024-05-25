#ifndef FZLVM_REGISTERS_SYSFLAGS_H
#define FZLVM_REGISTERS_SYSFLAGS_H

#include <bit>

namespace fzlvm::registers {
class SystemFlags {

  public:
    SystemFlags() : flags_{} { flags_.zero_flag = 1; }

    void ClearFlags() { flags_ = std::bit_cast<Flags>(0); };

    void SetZeroFlag() { flags_.zero_flag = 1; };
    void ClearZeroFlag() { flags_.zero_flag = 0; };
    bool ZeroFlag() const { return flags_.zero_flag != 0; }
    void SetCarryFlag() { flags_.carry_flag = 1; };
    bool CarryFlag() const { return flags_.carry_flag != 0; }
    void ClearCarryFlag() { flags_.carry_flag = 0; };
    void SetOverflowFlag() { flags_.overflow_flag = 1; };
    bool OverflowFlag() const { return flags_.overflow_flag != 0; }
    void ClearOverflowFlag() { flags_.overflow_flag = 0; };
    void SetNegativeFlag() { flags_.negative_flag = 1; };
    bool NegativeFlag() const { return flags_.negative_flag != 0; }
    void ClearNegativeFlag() { flags_.negative_flag = 0; };

  private:
    struct Flags {
        unsigned int zero_flag : 1;
        unsigned int carry_flag : 1;
        unsigned int overflow_flag : 1;
        unsigned int negative_flag : 1;
    };

    Flags flags_;
};
} // namespace fzlvm::registers

#endif