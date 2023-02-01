#ifndef CMD_RM_H
#define CMD_RM_H

#include <string>
#include <filesystem>

#include "src/global_var.h"

int cmd::rm(std::string arg,std::string dir){
    if(arg == "-rf"){
        // remove(fs_current_path.u8string() + dir);
        return 0;
    }else{
        std::cout << theme["warn"] << "Unknown argument" << reset;
        return 1;
    }
    return 0;
}

int cmd::rm(std::string file){
    // remove(fs_current_path.u8string() + file);
    return 0;
}

#endif