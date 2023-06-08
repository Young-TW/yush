#include "cmds.h"

#include <filesystem>
#include <string>

int cmds::mv(const std::vector<std::string>& arg, StreamManager& stream,
             VariableManager& vars) {
    if (arg.size() == 3) {
        std::filesystem::rename(arg[1], arg[2]);
        return 0;
    }

    return 1;
}
