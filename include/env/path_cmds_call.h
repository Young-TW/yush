#ifndef ENV_PATH_CMDS_CALL_H
#define ENV_PATH_CMDS_CALL_H

#include <vector>
#include <string>
#include <filesystem>

#include "variable_manager.h"
#include "stream_manager.hpp"
#include "feature/string_parser.h"

// check cmds from system $PATH
int cmd_call(std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager) {
    std::vector<std::string> cmd_paths = string_parser(variable_manager.get("PATH"), ':');
    std::string current_command = "";
    for (int i=0;i<arg.size();i++) {
        current_command = current_command + ' ' + arg[i];
    }
    for (auto cmd : cmd_paths) {
        std::filesystem::path cmd_path = cmd / std::filesystem::path(arg[0]);

        if(std::filesystem::exists(cmd_path) && std::filesystem::is_regular_file(cmd_path)) {
            return std::system(current_command.c_str());
        }
    }
    stream_manager.err() << "command `" << arg[0] << "` not found.\n";
    return 127;
}

#endif