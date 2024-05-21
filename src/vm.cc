#include "fzlvm/vm.h"
#include "fzlvm/instruction.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include "fzlvm/handlers/handlers.h"

void fzlvm::VM::LoadRom(const std::filesystem::path &rom_path) {
    std::ifstream rom_file(rom_path, std::ios::binary | std::ios::ate);

    if (!rom_file.is_open()) {
        std::cerr << "Failed to open the rom file." << std::endl;
        return;
    }

    std::streamsize rom_size = rom_file.tellg();
    rom_file.seekg(0, std::ios::beg);

    rom_.resize(static_cast<size_t>(rom_size));

    rom_file.read(reinterpret_cast<char *>(rom_.data()), rom_size);

    rom_file.close();
}

void fzlvm::VM::LoadRom(const std::vector<std::byte> &rom) { rom_ = rom; }

void fzlvm::VM::Step() {
    if (pc_ >= rom_.size()) {
        std::cout << "Reached end of ROM" << std::endl;
        return;
    }

    fzlvm::instruction::Opcode next_opcode =
        static_cast<fzlvm::instruction::Opcode>(NextByte());

    auto curr_instruction = fzlvm::instruction::Instruction(next_opcode);
    handlers::kInstructionHandlers.at(curr_instruction.GetInstructionCode())(
        curr_instruction, *this);
}

void fzlvm::VM::Exec() {
    while (pc_ < rom_.size()) {
        Step();
    }
}