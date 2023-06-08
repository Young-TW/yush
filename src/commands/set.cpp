#include "cmds.h"

#include <filesystem>
#include <string>

int cmds::set(const std::vector<std::string>& arg,
              StreamManager& stream,
              VariableManager& vars) {
    if (arg.size() != 3) {
        stream.err() << "Argument size error.\n";
        return 1;
    }

    vars.set(arg[1], arg[2]);

    return 0;
}
