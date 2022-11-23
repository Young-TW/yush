#ifndef CMD_ALIAS_H__
#define CMD_ALIAS_H__

#include <string>
#include <map>

#include "../global_var.h"

int alias(std::string i){
    // add command
    int found = i.find("=");
    // std::string cmd_name = i.substr(0, found);
    // std::string cmd_content = i.substr(found+1, i.size()-1);
    // alias_map.insert(cmd_name, cmd_content);
    return 0;
}

#endif