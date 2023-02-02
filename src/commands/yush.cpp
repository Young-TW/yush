#ifndef CMD_YUSH_H
#define CMD_YUSH_H

#include <string>
#include <filesystem>
#include <fstream>

#include "commands/cmds.h"
#include "shell.h"

int cmd::yush(const std::vector<std::string>& arg, std::istream& is, std::ostream& os, std::map<std::string, std::string>& variables) {
    if (arg.size() != 2) {
        return 1;
    }

    auto target = std::filesystem::path(variables.at("PWD")) / arg[1];
    if (!std::filesystem::is_regular_file(target)) {
        return 1;
    }

    return Shell(std::ifstream(target)).run();
}

#endif