#include "shell.h"

#include "gtest/gtest.h"

Shell shell;

TEST(Shell, run) { EXPECT_EQ(1, 1); }

TEST(Shell, function_requires_body) {
    Command cmd("function foo");
    cmd.parse();
    EXPECT_NE(shell.exec_cmd(cmd), 0);
}
