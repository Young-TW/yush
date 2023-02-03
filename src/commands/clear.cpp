#ifndef CMD_CLEAR_H
#define CMD_CLEAR_H

#include <string_view>

#include "commands/cmds.h"

int cmd::clear(const std::vector<std::string>& arg, std::istream& is, std::ostream& os, std::map<std::string, std::string>& variables) {
    std::string_view sys = variables.at("SYSTEM");
    if (sys != "Linux" && sys != "MacOS" && sys != "Unix") {
        system("CLS");
    } else {
        system("clear");
    }
    return 0;
}

#endif