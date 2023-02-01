#ifndef CMD_ALIAS_H
#define CMD_ALIAS_H

#include <string>
#include <map>

#include "src/global_var.h"

int cmd::alias(std::string input){
    // add command
    size_t found = input.find("=");
    // std::string cmd_name = i.substr(0, found);
    // std::string cmd_content = i.substr(found+1, i.size()-1);
    // alias_map.insert(cmd_name, cmd_content);
    return 0;
}

#endif