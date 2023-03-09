#include <string>
#include <filesystem>

#include "stream_manager.hpp"
#include "variable_manager.h"
#include "cmds.h"

int cmd::mv(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager) {
    if (arg.size() == 3) {
        std::filesystem::rename(arg[1], arg[2]);
        return 0;
    }

    return 1;
}