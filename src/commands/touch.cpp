#ifndef CMD_TOUCH_H
#define CMD_TOUCH_H

#include <string>
#include <filesystem>
#include <fstream>

#include "stream_manager.hpp"
#include "variable_manager.h"
#include "commands/cmds.h"

int cmd::touch(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager) {
    if (arg.size() != 2) {
        stream_manager.err() << "Argument size error.\n";
        return 1;
    }

    auto new_file = std::filesystem::path(variable_manager.get("PWD")) / arg[1];
    if (std::filesystem::exists(new_file)) {
        stream_manager.err() << "File already exists.\n";
        return 1;
    }

    std::ofstream fout(new_file);
    return 0;
}

#endif