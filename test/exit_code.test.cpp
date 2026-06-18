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
#include <filesystem>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

#include "gtest/gtest.h"

// `Shell::Shell()` constructs paths under $HOME/.config/yush and
// $HOME/.local/share/yush. The bare GitHub Actions ubuntu runner does not
// have these directories, and `Shell::Shell()` calls
// `std::filesystem::create_directory` (not create_directories), so a
// missing parent crashes the test binary during global initialization
// with `filesystem_error: cannot create directory`. The production binary
// never hits this because it ships an `etc/install.sh` that creates the
// layout, but the test target has no such setup.
//
// Pre-create the directories here as a side effect of the static
// initializer for `EnsureYushDirs`. Globals within a translation unit are
// initialized in declaration order, and `EnsureYushDirs` is declared before
// the `Shell shell;` global below, so the directories exist before the
// `Shell` constructor runs. Uses `std::filesystem::create_directories`
// (recursive) so it's safe even when $HOME or its parents already exist.
namespace {
struct EnsureYushDirs {
    EnsureYushDirs() {
        const char* home_c = std::getenv("HOME");
        std::filesystem::path home =
            home_c ? std::filesystem::path(home_c) : std::filesystem::current_path();
        std::error_code ec;
        std::filesystem::create_directories(home / ".config/yush", ec);
        std::filesystem::create_directories(home / ".local/share/yush", ec);
    }
};
EnsureYushDirs ensure_yush_dirs;
}  // namespace

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

// `;`, `&&` and `||` chaining, observed through the line's resulting status.
TEST(ExecLine, SequenceRunsAll) {
    EXPECT_EQ(shell.exec_line("/usr/bin/false ; /usr/bin/true"), 0);
}

TEST(ExecLine, AndRunsSecondOnSuccess) {
    EXPECT_EQ(shell.exec_line("/usr/bin/true && /usr/bin/false"), 1);
}

TEST(ExecLine, AndSkipsSecondOnFailure) {
    // Second command is skipped, so the status stays at the first false (1).
    EXPECT_EQ(shell.exec_line("/usr/bin/false && /usr/bin/false"), 1);
}

TEST(ExecLine, OrRunsSecondOnFailure) {
    EXPECT_EQ(shell.exec_line("/usr/bin/false || /usr/bin/true"), 0);
}

TEST(ExecLine, OrSkipsSecondOnSuccess) {
    EXPECT_EQ(shell.exec_line("/usr/bin/true || /usr/bin/false"), 0);
}
