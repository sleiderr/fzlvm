#ifndef FZLVM_HANDLERS_H_
#define FZLVM_HANDLERS_H_

#include "fzlvm/handlers/alu.h"
#include "fzlvm/handlers/jmp.h"

#include <unordered_map>

#include "fzlvm/instruction.h"
#include "fzlvm/vm.h"

namespace fzlvm::handlers {

using InstructionHandler = void (*)(fzlvm::instruction::Instruction,
                                    fzlvm::VM &);

inline void NopHandler(fzlvm::instruction::Instruction instruction,
                       fzlvm::VM &vm) {
    return;
};

static const std::unordered_map<fzlvm::instruction::InstructionCode,
                                InstructionHandler>
    kInstructionHandlers =
        std::unordered_map<fzlvm::instruction::InstructionCode,
                           InstructionHandler>{
            {instruction::InstructionCode::kNop, *NopHandler},
            {instruction::InstructionCode::kAdd, *alu::AddHandler},
            {instruction::InstructionCode::kSub, *alu::SubHandler},
            {instruction::InstructionCode::kNot, *alu::NotHandler},
            {instruction::InstructionCode::kAnd, *alu::AndHandler},
            {instruction::InstructionCode::kOr, *alu::OrHandler},
            {instruction::InstructionCode::kXor, *alu ::XorHandler},
            {instruction::InstructionCode::kShl, *alu ::ShlHandler},
            {instruction::InstructionCode::kShr, *alu ::ShrHandler},
            {instruction::InstructionCode::kCmp, *alu ::CmpHandler},
            {instruction::InstructionCode::kJmp, *JmpHandler},
        };
} // namespace fzlvm::handlers
#endif