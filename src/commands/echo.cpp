#ifndef CMD_ECHO_H
#define CMD_ECHO_H

#include <vector>
#include <string_view>

#include "commands/cmds.h"

int cmd::echo(const std::vector<std::string>& arg, std::istream& is, std::ostream& os, std::map<std::string, std::string>& variables) {
    if (arg[1] == "$system") {
        os << variables.at("SYSTEM");
    } else if (arg[1] == "$theme") {
        os << variables.at("COLOR_THEME");
    } else {
        for (size_t i = 1; i < arg[1].size(); ++i) {
            os << arg[1][i] << " ";
        }
    }
    return 0;
}

#endif