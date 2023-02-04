#ifndef CMD_RM_H
#define CMD_RM_H

#include <string>
#include <filesystem>

#include "stream_manager.hpp"
#include "variable_manager.h"
#include "commands/cmds.h"

int cmd::rm(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager){
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