#include "cmds.h"

#include <filesystem>
#include <string>

int cmds::cp(const std::vector<std::string>& arg, StreamManager& stream_manager,
             VariableManager& variable_manager) {
    if (arg.size() == 3) {
        return std::filesystem::copy_file(arg[1], arg[2]);
    }

    return 1;
}
