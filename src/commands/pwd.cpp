#include <fmt/format.h>

#include <filesystem>

#include "shell.h"

int Shell::cmd_pwd(const std::vector<std::string>& arg) {
    fmt::print("{}\n", std::filesystem::current_path().string());
    return 0;
}
