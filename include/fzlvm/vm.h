#ifndef FZLVM_VM_H_
#define FZLVM_VM_H_

#include <array>
#include <cstddef>
#include <filesystem>
#include <vector>

namespace fzlvm {

class VM {
  public:
    VM() : registers_{}, rom_{}, pc_{} {};

    unsigned int &GetRegister(size_t id) { return registers_[id]; }

    const unsigned int &GetRegister(size_t id) const { return registers_[id]; }

    void LoadRom(const std::filesystem::path &rom_path);
    void LoadRom(const std::vector<std::byte> &rom);

    std::byte NextByte() { return rom_[pc_++]; };

    void Step();
    void Exec();

  private:
    std::array<unsigned int, 32> registers_;
    std::vector<std::byte> rom_;
    size_t pc_;
};

} // namespace fzlvm

#endif