#ifndef FZLVM_HANDLERS_ALU_H_
#define FZLVM_HANDLERS_ALU_H_

#include "fzlvm/instruction.h"
#include "fzlvm/vm.h"

namespace fzlvm::handlers::alu {
void AddHandler(fzlvm::instruction::Instruction, fzlvm::VM &);
}

#endif