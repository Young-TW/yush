#ifndef _CMD_MKDIR_H_
#define _CMD_MKDIR_H_

#include <iostream>
#include <string>
#include <filesystem>

#include "src/global_var.h"

int yush::mkdir(){
    if(!exists(fs_current_path)){
        std::filesystem::create_directories(fs_current_path);
        fs_current_path = fs_current_path.parent_path();
        return 0;
    }
    return 0;
}

int yush::mkdir(std::string input){
    if(!exists(fs_current_path.append(input))){
        std::filesystem::create_directories(fs_current_path);
        fs_current_path = fs_current_path.parent_path();
        return 0;
    }else{
        std::cout << "directory already exists";
    }
    return 0;
}

#endif