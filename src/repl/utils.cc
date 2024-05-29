#include "fzlvm/instruction.h"
#include "fzlvm/registers/sysflags.h"
#include "fzlvm/repl.h"

#include <array>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "fzlvm/vm.h"

namespace fzlvm::repl::commands {
int PrintRegister(std::vector<std::string> args, fzlvm::repl::FzlRepl &repl) {
    fzlvm::VM &vm = repl.VM();

    if (args.size() == 0 || args[0] == "") {
        std::cout << "Usage: @register [register_id] / all." << std::endl;

        return 16;
    }

    try {
        int registerToPrint = std::stoi(args[0]);

        std::cout << "Value in register " << registerToPrint << " : "
                  << std::hex
                  << vm.GetRegister(static_cast<size_t>(registerToPrint))
                  << std::dec << std::endl;
    } catch (const std::invalid_argument &e) {
        if (args[0] == "all") {
            std::cout << "----- Registers dump -----" << std::endl;

            for (size_t i = 0; i < kRegisterCount; ++i) {
                std::cout << i << ": " << std::hex << vm.GetRegister(i)
                          << std::dec << std::endl;
            }

            std::cout << "--------------------------"
                      << "\n";
        } else {
            std::cout << "Invalid register specified." << std::endl;
        }
    } catch (const std::out_of_range &e) {
        std::cout << "Invalid register specified." << std::endl;
    }

    return 0;
}

int DebugSysFlags(std::vector<std::string> args, ::fzlvm::repl::FzlRepl &repl) {
    std::ostringstream output{};
    output << "System flags:";

    ::fzlvm::registers::SystemFlags sysflags = repl.VM().SysFlags();

    if (sysflags.ZeroFlag()) {
        output << " ZF,";
    }
    if (sysflags.CarryFlag()) {
        output << " CF,";
    }
    if (sysflags.OverflowFlag()) {
        output << " OF,";
    }
    if (sysflags.NegativeFlag()) {
        output << " NF,";
    }
    std::string final_output = output.str();
    final_output.erase(final_output.size() - 1, 1);

    std::cout << final_output << "\n";

    return 0;
}

int RawExec(std::vector<std::string> args, ::fzlvm::repl::FzlRepl &repl) {
    if (args.size() == 0 || args[0] == "") {
        std::cout << "Usage: @rexec [32bit instruction]" << std::endl;
    }

    try {
        long raw_instruction = std::stol(args[0], nullptr, 16);
        std::array<std::byte, 4> instruction_parts;

        // todo: check for endianness issues as this does not make much sense
        instruction_parts[2] = static_cast<std::byte>(raw_instruction & 0xff);
        instruction_parts[3] =
            static_cast<std::byte>((raw_instruction >> 8) & 0xff);
        instruction_parts[1] =
            static_cast<std::byte>((raw_instruction >> 16) & 0xff);
        instruction_parts[0] =
            static_cast<std::byte>((raw_instruction >> 24) & 0xff);

        auto instruction = ::fzlvm::instruction::Instruction(instruction_parts);

        repl.VM().SingleInstruction(instruction);
    } catch (const std::invalid_argument &e) {
        std::cerr << "Invalid instruction received" << std::endl;
    }

    return 0;
}
} // namespace fzlvm::repl::commands