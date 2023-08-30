#include "shell.h"

#include <string>

#include <fmt/format.h>

int Shell::cmd_alias(const std::vector<std::string>& arg, VariableManager& vars) {
    if (arg.size() != 3) {
        fmt::print(stderr, "Argument size error.\n");
        return 1;
    }

    this->alias_map.emplace(arg[1], arg[2]);
    return 0;
}
