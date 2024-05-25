#ifndef FZLVM_HANDLERS_ALU_H_
#define FZLVM_HANDLERS_ALU_H_

#include "fzlvm/instruction.h"
#include "fzlvm/vm.h"

namespace fzlvm::handlers::alu {

void FlagUpdate(fzlvm::VM &);

void AddHandler(fzlvm::instruction::Instruction, fzlvm::VM &);
void SubHandler(fzlvm::instruction::Instruction, fzlvm::VM &);
void NotHandler(fzlvm::instruction::Instruction, fzlvm::VM &);
void AndHandler(fzlvm::instruction::Instruction, fzlvm::VM &);
void OrHandler(fzlvm::instruction::Instruction, fzlvm::VM &);
void XorHandler(fzlvm::instruction::Instruction, fzlvm::VM &);
void ShlHandler(fzlvm::instruction::Instruction, fzlvm::VM &);
void ShrHandler(fzlvm::instruction::Instruction, fzlvm::VM &);
void CmpHandler(fzlvm::instruction::Instruction, fzlvm::VM &);
} // namespace fzlvm::handlers::alu

#endif