#include "fzlvm/repl.h"

#include <iostream>
#include <stdexcept>
#include <string>

int main(int argc, char **argv) {
    fzlvm::repl::FzlRepl repl{};

    std::cout << "Welcome to the FZL virtual machine! \n" << std::endl;

    fzlvm::repl::RegisterBaseMetaCommandHandlers();
    repl.RunMainLoop();
}

std::unordered_map<std::string,
                   std::shared_ptr<int (*)(std::vector<std::string> args,
                                           fzlvm::repl::FzlRepl &)>>
    fzlvm::repl::FzlRepl::meta_commands_{};

void fzlvm::repl::FzlRepl::RegisterMetaCommand(
    std::string name,
    std::shared_ptr<int (*)(std::vector<std::string>, FzlRepl &)> handler) {
    meta_commands_.insert(std::make_pair(name, handler));
}

void fzlvm::repl::FzlRepl::RunMainLoop() {
    std::string user_input{};

    for (;;) {
        std::cout << ">>> ";
        std::getline(std::cin, user_input);

        // internal meta commands start with an @
        if (user_input.starts_with("@")) {
            user_input.erase(0, 1);
            size_t command_identifier_end_pos = user_input.find(" ");
            std::string command =
                user_input.substr(0, command_identifier_end_pos);
            user_input.erase(0, command.size() + 1);

            std::vector<std::string> args{};
            size_t pos{};

            while ((pos = user_input.find(" ")) != std::string::npos) {
                args.push_back(user_input.substr(0, pos));
                user_input.erase(0, pos + 1);
            }

            args.push_back(user_input);
            user_input.erase(0, std::string::npos);

            try {
                std::shared_ptr<FzlMetaCommandHandler> &handler =
                    meta_commands_.at(command);

                (*handler)(args, *this);
            } catch (const std::out_of_range &e) {
                std::cout << "Unknown command" << std::endl;
            }
        }
    }
}

void fzlvm::repl::RegisterBaseMetaCommandHandlers() {
    fzlvm::repl::FzlRepl::RegisterMetaCommand(
        "register", make_shared<fzlvm::repl::FzlMetaCommandHandler>(
                        commands::PrintRegister));
    fzlvm::repl::FzlRepl::RegisterMetaCommand(
        "sysflags", make_shared<fzlvm::repl::FzlMetaCommandHandler>(
                        commands::DebugSysFlags));
    fzlvm::repl::FzlRepl::RegisterMetaCommand(
        "rexec",
        make_shared<fzlvm::repl::FzlMetaCommandHandler>(commands::RawExec));
}