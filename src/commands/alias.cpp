#include "shell.h"

#include <string>

#include <fmt/format.h>

int Shell::cmd_alias(const std::vector<std::string>& arg) {
    if (arg.size() != 3) {
        fmt::print(stderr, "Argument size error.\n");
        return 1;
    }

    // this->alias.set(arg[1], arg[2]);
    return 0;
}