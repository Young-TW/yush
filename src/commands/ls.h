#ifndef _CMD_LS_H_
#define _CMD_LS_H_

#include <iostream>
#include <filesystem>

#include "../global_var.h"

int yush::ls(){
    if(!exists(fs_current_path)){
        return 1;
    }
    std::filesystem::directory_iterator list(fs_current_path);
    for(auto& it : list){
        if(it.path().filename().u8string()[0] != '.'){
            if(it.is_directory()){
                std::cout << theme["dir"] << it.path().filename().u8string() << reset;
                std::cout << "/";
            }else{
                std::cout << it.path().filename().u8string();
            }
            std::cout << "\t";
        }
    }
    return 0;
}

int yush::la(){
    if(!exists(fs_current_path)){
        return 1;
    }
    std::filesystem::directory_iterator list(fs_current_path);
    for(auto& it : list){
        std::cout << it.path().filename().u8string();
        if(it.is_directory()){
            std::cout << "/";
        }
        std::cout << "\n";
    }
    return 0;
}

#endif