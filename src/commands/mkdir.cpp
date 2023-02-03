#ifndef CMD_MKDIR_H
#define CMD_MKDIR_H

#include <string>
#include <filesystem>

#include "commands/cmds.h"

int cmd::mkdir(const std::vector<std::string>& arg, std::istream& is, std::ostream& os, std::map<std::string, std::string>& variables) {
    if (arg.size() != 2) {
        os << variables.at("COLOR_WARN") << "Error: argument size error." << variables.at("COLOR_RESET");
        return 1;
    }

    auto new_directory = std::filesystem::path(variables.at("PWD")) / arg[1];
    if (!exists(new_directory)) {
        std::filesystem::create_directories(new_directory);
        return 0;
    } else {
        os << variables.at("COLOR_WARN") << "Error: directory already exists" << variables.at("COLOR_RESET");
        return 1;
    }
}

#endif