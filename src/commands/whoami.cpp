#ifndef CMD_WHOAMI_H
#define CMD_WHOAMI_H

#include <string_view>

#include "commands/cmds.h"

int cmd::whoami(const std::vector<std::string>& arg, std::istream& is, std::ostream& os, std::map<std::string, std::string>& variables){
    os << variables.at("USER");
    return 0;
}

#endif