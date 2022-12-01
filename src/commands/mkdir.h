#ifndef _CMD_MKDIR_H_
#define _CMD_MKDIR_H_

#include <iostream>
#include <string>
#include <filesystem>

#include "../global_var.h"

int mkdir(){
    if(!exists(fs_current_path)){
        std::filesystem::create_directories(fs_current_path);
        fs_current_path = fs_current_path.parent_path();
        return 0;
    }
    return 0;
}

int mkdir(std::string i){
    if(!exists(fs_current_path.append(i))){
        std::filesystem::create_directories(fs_current_path);
        fs_current_path = fs_current_path.parent_path();
        return 0;
    }else{
        std::cout << "directory already exists";
    }
    return 0;
}

#endif