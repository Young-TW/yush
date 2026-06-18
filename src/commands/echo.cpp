#include <vector>

#include "fmt/format.h"

#include "shell.h"

int Shell::cmd_echo(const std::vector<std::string>& arg) {
    std::size_t first{1};
    bool newline{true};
    if (arg.size() > 1 && arg[1] == "-n") {
        newline = false;
        first = 2;
    }

    for (std::size_t i{first}; i < arg.size(); ++i) {
        if (i > first) {
            fmt::print(" ");
        }
        fmt::print("{}", arg[i]);
    }

    if (newline) {
        fmt::print("\n");
    }
    return 0;
}
