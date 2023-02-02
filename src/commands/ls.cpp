#ifndef CMD_LS_H
#define CMD_LS_H

#include <filesystem>

#include "commands/cmds.h"

int cmd::ls(const std::vector<std::string>& arg, std::istream& is, std::ostream& os, std::map<std::string, std::string>& variables) {
    std::filesystem::path current_path(variables.at("PWD"));

    if (!std::filesystem::exists(current_path)) {
        return 1;
    }

    std::filesystem::directory_iterator list(current_path);
    for (auto& it : list) {
        if (it.path().filename().string()[0] != '.') {
            if (it.is_directory()) {
                os << variables.at("COLOR_DIR") << it.path().filename().string() << '/' << variables.at("COLOR_RESET");
            } else {
                os << it.path().filename().string();
            }
            os << "\t";
        }
    }
    return 0;
}

int cmd::la(const std::vector<std::string>& arg, std::istream& is, std::ostream& os, std::map<std::string, std::string>& variables) {
    std::filesystem::path current_path(variables.at("PWD"));

    if (!std::filesystem::exists(current_path)) {
        return 1;
    }

    std::filesystem::directory_iterator list(current_path);
    for (auto& it : list) {
        if (it.is_directory()) {
            os << variables.at("COLOR_DIR") << it.path().filename().string() << '/' << variables.at("COLOR_RESET");
        } else {
            os << it.path().filename().string();
        }
        os << "\t";
    }
    return 0;
}

#endif