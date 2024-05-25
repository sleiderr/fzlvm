#ifndef FZLVM_REPL_H
#define FZLVM_REPL_H

#include <memory>
#include <unordered_map>
#include <vector>

#include "fzlvm/vm.h"

namespace fzlvm::repl {

void RegisterBaseMetaCommandHandlers();

class FzlRepl {
  public:
    FzlRepl() : vm_{}, history_{} {};
    void RunMainLoop();

    static void RegisterMetaCommand(
        std::string,
        std::shared_ptr<int (*)(std::vector<std::string> args, FzlRepl &)>);

  private:
    fzlvm::VM vm_;
    std::vector<std::string> history_;
    static std::unordered_map<
        std::string,
        std::shared_ptr<int (*)(std::vector<std::string> args, FzlRepl &)>>
        meta_commands_;
};

using FzlMetaCommandHandler = int (*)(std::vector<std::string>, FzlRepl &);
} // namespace fzlvm::repl

#endif