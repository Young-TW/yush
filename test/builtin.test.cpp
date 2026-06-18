// Unit tests for the shell builtins (cd, echo, pwd, ls, set, alias), driven
// through the public exec_statement() entry point. Output-producing builtins
// are captured by redirecting to a temp file; state-changing builtins are
// checked via the shell's public vars/functions and the process cwd.

#include "shell.h"

#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>

#include <unistd.h>

#include "gtest/gtest.h"

extern Shell shell;

namespace {

std::string slurp(const std::string& path) {
    std::ifstream in(path);
    return std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
}

std::string temp_path(const std::string& tag) {
    return "/tmp/yush_builtin_" + std::to_string(getpid()) + "_" + tag;
}

}  // namespace

TEST(Builtin, SetStoresVariable) {
    shell.exec_statement("set BUILTIN_SET_KEY hello");
    EXPECT_EQ(shell.vars.get("BUILTIN_SET_KEY"), "hello");
}

TEST(Builtin, AliasStoresDefinition) {
    shell.exec_statement("alias builtin_gg \"echo aliased\"");
    EXPECT_EQ(shell.functions.get("builtin_gg"), "echo aliased");
}

TEST(Builtin, EchoWritesArguments) {
    const std::string out{temp_path("echo")};
    shell.exec_statement("echo hello world > " + out);
    EXPECT_EQ(slurp(out), "hello world\n");
    std::filesystem::remove(out);
}

TEST(Builtin, EchoDashNSuppressesNewline) {
    const std::string out{temp_path("echon")};
    shell.exec_statement("echo -n nonl > " + out);
    EXPECT_EQ(slurp(out), "nonl");
    std::filesystem::remove(out);
}

TEST(Builtin, CdChangesDirectory) {
    std::filesystem::path original{std::filesystem::current_path()};
    std::filesystem::path dir{std::filesystem::temp_directory_path()};
    shell.exec_statement("cd " + dir.string());
    EXPECT_EQ(std::filesystem::current_path(), std::filesystem::canonical(dir));
    std::filesystem::current_path(original);
}

TEST(Builtin, CdDashReturnsToPrevious) {
    std::filesystem::path original{std::filesystem::current_path()};
    std::filesystem::path dir{std::filesystem::temp_directory_path()};
    shell.exec_statement("cd " + dir.string());
    shell.exec_statement("cd -");
    EXPECT_EQ(std::filesystem::current_path(), original);
    std::filesystem::current_path(original);
}

TEST(Builtin, PwdPrintsCurrentDirectory) {
    std::filesystem::path original{std::filesystem::current_path()};
    const std::string out{temp_path("pwd")};
    shell.exec_statement("cd " + std::filesystem::temp_directory_path().string());
    shell.exec_statement("pwd > " + out);
    std::string content{slurp(out)};
    if (!content.empty() && content.back() == '\n') {
        content.pop_back();
    }
    EXPECT_EQ(std::filesystem::path(content), std::filesystem::current_path());
    std::filesystem::remove(out);
    std::filesystem::current_path(original);
}

TEST(Builtin, LsListsEntries) {
    std::filesystem::path original{std::filesystem::current_path()};
    std::filesystem::path dir{temp_path("lsdir")};
    std::filesystem::create_directories(dir);
    std::ofstream(dir / "marker_file.txt").close();

    const std::string out{temp_path("ls")};
    shell.exec_statement("cd " + dir.string());
    shell.exec_statement("ls > " + out);
    EXPECT_NE(slurp(out).find("marker_file.txt"), std::string::npos);

    std::filesystem::current_path(original);
    std::filesystem::remove(out);
    std::filesystem::remove_all(dir);
}
