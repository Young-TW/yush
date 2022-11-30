#ifndef CMD_RM_H__
#define CMD_RM_H__

#include <string>
#include <filesystem>

#include "../global_var.h"

int rm(std::string arg,std::string dir){
    if(arg == "-rf"){
        // remove(fs_current_path.u8string() + dir);
        return 0;
    }else{
        std::cout << theme["warn"] << "Unknown argument" << reset;
        return 1;
    }
    return 0;
}

int rm(std::string file){
    // remove(fs_current_path.u8string() + file);
    return 0;
}

#endif