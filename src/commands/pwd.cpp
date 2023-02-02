#ifndef CMD_PWD_H
#define CMD_PWD_H

#include <filesystem>

#include "commands/cmds.h"

int cmd::pwd(const std::vector<std::string>& arg, std::istream& is, std::ostream& os, std::map<std::string, std::string>& variables){
    os << variables.at("PWD");
    return 0;
}

#endif