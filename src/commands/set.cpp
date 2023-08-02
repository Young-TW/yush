#include "cmds.h"

#include <filesystem>
#include <string>

#include <fmt/format.h>

int cmds::set(const std::vector<std::string>& arg, VariableManager& vars) {
    if (arg.size() != 3) {
        // stream.err() << "Argument size error.\n";
        return 1;
    }

    vars.set(arg[1], arg[2]);

    return 0;
}
