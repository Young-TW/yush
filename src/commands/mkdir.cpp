#include <filesystem>

#include "stream_manager.hpp"
#include "variable_manager.h"
#include "cmds.h"

int cmd::mkdir(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager) {
    if (arg.size() != 2) {
        stream_manager.err() << "Argument size error.\n";
        return 1;
    }

    auto new_directory = std::filesystem::current_path() / arg[1];
    if (!exists(new_directory)) {
        std::filesystem::create_directories(new_directory);
        return 0;
    } else {
        stream_manager.err() << "Directory already exists.\n";
        return 1;
    }
}