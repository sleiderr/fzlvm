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
            {fzlvm::instruction::InstructionCode::kAdd, *alu::AddHandler}};
} // namespace fzlvm::handlers
#endif