#include "fzlvm/vm.h"

#include <gtest/gtest.h>

TEST(VM, EmptyRegistersInitially) {
    fzlvm::VM testVM{};
    EXPECT_EQ(testVM.GetRegister(0), 0);
}