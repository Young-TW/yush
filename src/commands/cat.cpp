#ifndef CMD_CAT_H
#define CMD_CAT_H

#include <string>
#include <filesystem>
#include <fstream>

#include "commands/cmds.h"

int cmd::cat(const std::vector<std::string>& arg, std::istream& is, std::ostream& os, std::map<std::string, std::string>& variables) {
    if (arg.size() != 2) {
        return 1;
    }

    auto target_file = std::filesystem::path(variables.at("PWD")) / arg[1];
    if (!std::filesystem::is_regular_file(target_file)) {
        return 1;
    }

    std::ifstream fin(target_file);
    std::string str((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
    os << str;

    return 0;
}

#endif