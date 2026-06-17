// Regression test for issue #40:
//   `Shell::exec_file` returned the raw `waitpid()` status word instead of
//   decoding it with WEXITSTATUS / WIFSIGNALED. The raw status encodes the
//   exit code in bits 8-15, so a child that exited with code 1 caused
//   the shell to record 256, a child that exited with 0 returned 0 only
//   by coincidence, and a child killed by a signal returned a completely
//   wrong number.
//
// These tests exercise `Shell::exec_cmd` end-to-end so we can observe the
// actual returned exit code (the binary's own process exit code truncates
// to 0-255, which would mask the bug for codes != 1, 257, etc.).

#include "command.h"
#include "shell.h"

#include <cstdlib>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

#include "gtest/gtest.h"

// `command.cpp` declares `extern Shell shell;` and uses it during
// `Command::parse()`. The production binary defines that global in
// main.cpp, but main.cpp is intentionally excluded from the test target,
// so we provide a test-local definition here with external linkage.
// Using a default-constructed shell is fine: exec_cmd / exec_file do not
// read shell state.
Shell shell;

namespace {

// Helper: write a one-line shell script that exits with the given code and
// make it executable. Returns the absolute path of the script.
std::string write_exit_script(int code) {
    std::string path = "/tmp/yush_test_exit_" + std::to_string(getpid()) + "_" +
                       std::to_string(code) + ".sh";
    std::ofstream out(path);
    out << "#!/bin/sh\n";
    out << "exit " << code << "\n";
    out.close();
    if (::chmod(path.c_str(), 0755) != 0) {
        // Tests will fail with a clear "file not found" downstream.
        return {};
    }
    return path;
}

}  // namespace

TEST(ExitCode, TrueReturnsZero) {
    Command cmd("/usr/bin/true");
    cmd.parse();
    EXPECT_EQ(shell.exec_cmd(cmd), 0);
}

TEST(ExitCode, FalseReturnsOne) {
    Command cmd("/usr/bin/false");
    cmd.parse();
    // Before the fix: this returned 256 (raw status word).
    EXPECT_EQ(shell.exec_cmd(cmd), 1);
}

TEST(ExitCode, ScriptExit42) {
    const std::string path = write_exit_script(42);
    ASSERT_FALSE(path.empty());
    Command cmd(path);
    cmd.parse();
    // Before the fix: this returned 42 << 8 = 10752.
    EXPECT_EQ(shell.exec_cmd(cmd), 42);
}

TEST(ExitCode, ScriptExitZero) {
    // Sanity check that exit 0 round-trips correctly through the fixed path
    // (it was correct before too, but only by coincidence).
    const std::string path = write_exit_script(0);
    ASSERT_FALSE(path.empty());
    Command cmd(path);
    cmd.parse();
    EXPECT_EQ(shell.exec_cmd(cmd), 0);
}

TEST(ExitCode, ScriptExitOne) {
    // Distinct from /usr/bin/false to guard against any test-fixture caching.
    const std::string path = write_exit_script(1);
    ASSERT_FALSE(path.empty());
    Command cmd(path);
    cmd.parse();
    EXPECT_EQ(shell.exec_cmd(cmd), 1);
}
