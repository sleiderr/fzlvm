#ifndef FZLVM_HANDLERS_H_
#define FZLVM_HANDLERS_H_

#include "fzlvm/handlers/alu.h"

#include <unordered_map>

#include "fzlvm/instruction.h"
#include "fzlvm/vm.h"

namespace fzlvm::handlers {

using InstructionHandler = void (*)(fzlvm::instruction::Instruction,
                                    fzlvm::VM &);

static const std::unordered_map<fzlvm::instruction::InstructionCode,
                                InstructionHandler>
    kInstructionHandlers =
        std::unordered_map<fzlvm::instruction::InstructionCode,
                           InstructionHandler>{
            {instruction::InstructionCode::kAdd, *alu::AddHandler},
            {instruction::InstructionCode::kSub, *alu::SubHandler},
            {instruction::InstructionCode::kNot, *alu::NotHandler},
            {instruction::InstructionCode::kAnd, *alu::AndHandler},
            {instruction::InstructionCode::kOr, *alu::OrHandler},
            {instruction::InstructionCode::kXor, *alu ::XorHandler},
            {instruction::InstructionCode::kShl, *alu ::ShlHandler},
            {instruction::InstructionCode::kShr, *alu ::ShrHandler},
        };
} // namespace fzlvm::handlers
#endif