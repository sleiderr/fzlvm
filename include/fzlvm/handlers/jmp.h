#ifndef FZLVM_HANDLERS_JMP_H_
#define FZLVM_HANDLERS_JMP_H_

#include "fzlvm/instruction.h"
#include "fzlvm/vm.h"

namespace fzlvm::handlers {
enum class JmpConditions : size_t {
    kNone,
    kZero,
    kNonZero,
    kGreater,
    kLesser,
    kCarry,
    kNoCarry,
    kOverflow,
};
void JmpHandler(fzlvm::instruction::Instruction, fzlvm::VM &);
} // namespace fzlvm::handlers

#endif