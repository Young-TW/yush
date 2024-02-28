#include "shell.h"

#include "command.h"

#include <string>

#include <fmt/format.h>

int Shell::cmd_alias(const std::vector<std::string>& arg) {
    if (arg.size() != 3) {
        fmt::print(stderr, "Argument size error.\n");
        return 1;
    }

    Command alias_cmd = Command(arg[2]);

    this->alias.try_emplace(arg[1], alias_cmd);
    return 0;
}