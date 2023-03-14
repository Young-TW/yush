#ifndef ENV_PATH_CMDS_CALL_H
#define ENV_PATH_CMDS_CALL_H

#include <vector>
#include <string>
#include <filesystem>

#include "variable_manager.h"
#include "stream_manager.hpp"
#include "feature/string_parser.h"

#ifdef _WIN32 // Both of 32-bit and 64-bit define this.

// check cmds from system $PATH
int cmd_call(std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager) {
    std::vector<std::string> cmd_paths = string_parser(variable_manager.get("PATH"), ';');
    for (auto cmd : cmd_paths) {
        std::filesystem::path cmd_path = cmd / std::filesystem::path(arg[0] + ".exe");
        if(std::filesystem::exists(cmd_path) && std::filesystem::is_regular_file(cmd_path)) {
            std::string cmd_args = "";
            for (int i=1;i<arg.size();i++) {
                cmd_args = cmd_args + ' ' + arg[i];
            }
            return std::system((arg[0] + ".exe" + ' ' + cmd_args).c_str());
        }
    }
    stream_manager.err() << "command `" << arg[0] << "` not found.\n";
    return 127;
}

#elif __linux__

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

#elif __APPLE__

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

#endif
