#include "shell.h"

#include <iostream>
#include <string_view>
#include <vector>

#include <fmt/format.h>

int Shell::cmd_echo(const std::vector<std::string>& arg, VariableManager& vars) {
    for (size_t i = 1; i < arg.size(); i++) {
        fmt::print("{} ", arg[i]);
    }

    fmt::print("\n");
    return 0;
}
