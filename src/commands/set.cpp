#include "cmds.h"

#include <filesystem>
#include <string>

int cmds::set(const std::vector<std::string>& arg,
              StreamManager& stream_manager,
              VariableManager& variable_manager) {
    if (arg.size() != 3) {
        stream_manager.err() << "Argument size error.\n";
        return 1;
    }

    variable_manager.set(arg[1], arg[2]);

    return 0;
}
