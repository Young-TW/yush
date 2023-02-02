#ifndef CMD_TOUCH_H
#define CMD_TOUCH_H

#include <string>
#include <filesystem>
#include <fstream>

#include "commands/cmds.h"

int cmd::touch(const std::vector<std::string>& arg, std::istream& is, std::ostream& os, std::map<std::string, std::string>& variables) {
    if (arg.size() != 2) {
        return 1;
    }

    auto new_file = std::filesystem::path(variables.at("PWD")) / arg[1];
    if (std::filesystem::exists(new_file)) {
        os << "file already exists";
        return 1;
    }

    std::ofstream fout(new_file);
    return 0;
}

#endif