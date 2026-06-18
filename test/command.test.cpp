#include "command.h"

#include <vector>

#include "shell.h"

#include "gtest/gtest.h"

extern Shell shell;

namespace {

std::vector<std::string> parse_args(const std::string& line) {
    Command cmd(line);
    cmd.parse();
    return cmd.arg();
}

}  // namespace

TEST(Command, SplitsOnWhitespace) {
    EXPECT_EQ(parse_args("echo a b c"),
              (std::vector<std::string>{"echo", "a", "b", "c"}));
}

TEST(Command, CollapsesExtraSpaces) {
    EXPECT_EQ(parse_args("  echo   a   b  "),
              (std::vector<std::string>{"echo", "a", "b"}));
}

TEST(Command, DoubleQuotesKeepSpaces) {
    EXPECT_EQ(parse_args("echo \"a b\" c"),
              (std::vector<std::string>{"echo", "a b", "c"}));
}

TEST(Command, SingleQuotesAreLiteral) {
    EXPECT_EQ(parse_args("echo '$HOME'"),
              (std::vector<std::string>{"echo", "$HOME"}));
}

TEST(Command, ExpandsVariable) {
    shell.vars.set("GREETING", "hi");
    EXPECT_EQ(parse_args("echo $GREETING"),
              (std::vector<std::string>{"echo", "hi"}));
}

TEST(Command, ExpandsBracedVariable) {
    shell.vars.set("X", "val");
    EXPECT_EQ(parse_args("echo ${X}end"),
              (std::vector<std::string>{"echo", "valend"}));
}

TEST(Command, ConcatenatesAroundVariable) {
    shell.vars.set("DIR", "home");
    EXPECT_EQ(parse_args("echo /$DIR/x"),
              (std::vector<std::string>{"echo", "/home/x"}));
}

TEST(Command, ExpandsInsideDoubleQuotes) {
    shell.vars.set("WHO", "world");
    EXPECT_EQ(parse_args("echo \"hello $WHO\""),
              (std::vector<std::string>{"echo", "hello world"}));
}

TEST(Command, BackslashEscapesSpace) {
    EXPECT_EQ(parse_args("echo a\\ b"),
              (std::vector<std::string>{"echo", "a b"}));
}

TEST(Command, HashStartsComment) {
    EXPECT_EQ(parse_args("echo a # this is ignored"),
              (std::vector<std::string>{"echo", "a"}));
}

TEST(Command, HashInWordIsLiteral) {
    EXPECT_EQ(parse_args("echo a#b"),
              (std::vector<std::string>{"echo", "a#b"}));
}

TEST(Command, AliasForwardsArguments) {
    shell.functions.set("ll", "ls -la");
    EXPECT_EQ(parse_args("ll /tmp"),
              (std::vector<std::string>{"ls", "-la", "/tmp"}));
}

TEST(Command, AliasCycleTerminates) {
    // An alias that refers to itself must not loop forever.
    shell.functions.set("loopcmd", "loopcmd x");
    EXPECT_EQ(parse_args("loopcmd"),
              (std::vector<std::string>{"loopcmd", "x"}));
}
