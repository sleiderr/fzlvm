#ifndef FZLVM_VM_H_
#define FZLVM_VM_H_

#include <array>
#include <cstddef>
#include <filesystem>
#include <span>
#include <stdexcept>
#include <vector>

#include "fzlvm/instruction.h"
#include "fzlvm/registers/sysflags.h"

namespace fzlvm {

const size_t kRegisterCount = 32;

class VM {
  public:
    VM() : registers_{}, rom_{}, pc_{}, sys_flags_{} {};

    unsigned int &GetRegister(size_t id) {
        if (id >= kRegisterCount) {
            throw std::out_of_range("Invalid register id.");
        }
        return registers_[id];
    }

    const unsigned int &GetRegister(size_t id) const { return registers_[id]; }

    void LoadRom(const std::filesystem::path &rom_path);
    void LoadRom(const std::vector<std::byte> &&rom);

    size_t &GetProgramCounter() { return pc_; }
    const size_t MaxRomAddress() const { return rom_.size(); }

    registers::SystemFlags &SysFlags() { return sys_flags_; }

    std::byte NextByte() { return rom_[pc_++]; };
    std::span<std::byte, 4> NextBytecode() {
        auto dynamic_span = rom_span_.subspan(pc_, 4);

        pc_ += 4;
        return std::span<std::byte, 4>(dynamic_span.data(), 4);
    };

    void Step();
    void SingleInstruction(instruction::Instruction);
    void Exec();

  private:
    std::array<unsigned int, kRegisterCount> registers_;
    registers::SystemFlags sys_flags_;
    std::vector<std::byte> rom_;
    std::span<std::byte> rom_span_;
    size_t pc_;
};

} // namespace fzlvm

#endif