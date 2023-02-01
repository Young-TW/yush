#ifndef CMD_CD_H
#define CMD_CD_H

#include <iostream>
#include <string>
#include <filesystem>

#include "src/global_var.h"

int cmd::cd_single(std::string input){
    std::cout << fs_current_path << std::endl;
    if(input == ".."){
        fs_current_path = fs_current_path.parent_path();
        return 0;
    }else if(input == "/"){
        fs_current_path = fs_current_path.root_path();
        return 0;
    }else if(input == "~"){
        fs_current_path = current_user.home_dir;
        return 0;
    }else if(is_directory(fs_current_path.append(input))){
        return 0;
    }else{
        std::cout << input << " is not a directory";
        return 1;
    }
    return 0;
}

int cmd::cd(std::string input){
    std::filesystem::path current_path_backup = fs_current_path;
    for (size_t i=0; i<input.size();) {
        auto slash = input.find('/');
        if (slash == std::string::npos){
            slash = input.size();
        }
        if(cd_single(input.substr(i, slash))){
            fs_current_path = current_path_backup;
            return 1;
        }
        i += slash+1;
    }
    return 0;
}

#endif