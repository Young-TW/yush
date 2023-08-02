#include "cmds.h"

#include <filesystem>

#include <fmt/format.h>

int cmds::pwd(const std::vector<std::string>& arg, VariableManager& vars) {
    fmt::print("{}\n", std::filesystem::current_path().string());
    return 0;
}
