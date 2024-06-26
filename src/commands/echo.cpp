#include <iostream>
#include <vector>

#include "fmt/format.h"

#include "shell.h"

int Shell::cmd_echo(const std::vector<std::string>& arg) {
    for (size_t i = 1; i < arg.size(); i++) {
        fmt::print("{} ", arg[i]);
    }

    fmt::print("\n");
    return 0;
}
