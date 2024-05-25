#ifndef FZLVM_VM_H_
#define FZLVM_VM_H_

#include <array>
#include <cstddef>
#include <filesystem>
#include <span>
#include <vector>

#include "fzlvm/registers/sysflags.h"

namespace fzlvm {

class VM {
  public:
    VM() : registers_{}, rom_{}, pc_{} {};

    unsigned int &GetRegister(size_t id) { return registers_[id]; }

    const unsigned int &GetRegister(size_t id) const { return registers_[id]; }

    void LoadRom(const std::filesystem::path &rom_path);
    void LoadRom(const std::vector<std::byte> &&rom);

    registers::SystemFlags &SysFlags() { return sys_flags_; }

    std::byte NextByte() { return rom_[pc_++]; };
    std::span<std::byte, 4> NextBytecode() {
        auto dynamic_span = rom_span_.subspan(pc_, 4);

        pc_ += 4;
        return std::span<std::byte, 4>(dynamic_span.data(), 4);
    };

    void Step();
    void Exec();

  private:
    std::array<unsigned int, 32> registers_;
    registers::SystemFlags sys_flags_;
    std::vector<std::byte> rom_;
    std::span<std::byte> rom_span_;
    size_t pc_;
};

} // namespace fzlvm

#endif