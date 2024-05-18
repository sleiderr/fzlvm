#ifndef FZLVM_VM_H_
#define FZLVM_VM_H_

#include <array>

namespace fzlvm {

class VM {
  public:
    VM() : registers_{} {};

    unsigned int &GetRegister(size_t id) { return registers_[id]; }

    const unsigned int &GetRegister(size_t id) const { return registers_[id]; }

  private:
    std::array<unsigned int, 32> registers_;
};

} // namespace fzlvm

#endif