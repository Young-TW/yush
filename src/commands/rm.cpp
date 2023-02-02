#ifndef CMD_RM_H
#define CMD_RM_H

#include <string>
#include <filesystem>

#include "commands/cmds.h"

int cmd::rm(const std::vector<std::string>& arg, std::istream& is, std::ostream& os, std::map<std::string, std::string>& variables){
    // if(arg == "-rf"){
    //     // remove(fs_current_path.u8string() + dir);
    //     return 0;
    // }else{
    //     os << theme["warn"] << "Unknown argument" << reset;
    //     return 1;
    // }
    return 0;
}

#endif