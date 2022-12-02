#ifndef _CMD_RM_H_
#define _CMD_RM_H_

#include <string>
#include <filesystem>

#include "../global_var.h"

int yush::rm(std::string arg,std::string dir){
    if(arg == "-rf"){
        // remove(fs_current_path.u8string() + dir);
        return 0;
    }else{
        std::cout << theme["warn"] << "Unknown argument" << reset;
        return 1;
    }
    return 0;
}

int yush::rm(std::string file){
    // remove(fs_current_path.u8string() + file);
    return 0;
}

#endif