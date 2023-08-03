#include "cmds.h"

#include <iostream>
#include <string_view>
#include <vector>

#include <fmt/format.h>

int cmds::echo(const std::vector<std::string>& arg, VariableManager& vars) {
    if (arg[1][0] == '$') {
        if (vars.exist(arg[1].substr(1, arg[1].size() - 1))) {
            fmt::print("{}\n", vars.get(arg[1].substr(1, arg[1].size() - 1)));
            return 0;
        }
        std::cerr << "Variable not found\n";
        return 1;
    }

    for (size_t i = 1; i < arg.size(); i++) {
        fmt::print("{} ", arg[i]);
    }

    fmt::print("\n");
    return 0;
}
