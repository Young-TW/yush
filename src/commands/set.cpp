#include <fmt/format.h>

#include <filesystem>
#include <iostream>
#include <string>

#include "shell.h"

int Shell::cmd_set(const std::vector<std::string>& arg) {
    if (arg.size() != 3) {
        fmt::print(stderr, "Argument size error.\n");
        return 1;
    }

    vars.set(arg[1], arg[2]);

    return 0;
}
