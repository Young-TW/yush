#ifndef CMD_CD_H__
#define CMD_CD_H__

#include <iostream>
#include <string>
#include <filesystem>

#include "../global_var.h"

int cd_single(std::string input){
    std::filesystem::path if_fail = fs_current_path;
    if(input == ".."){
        fs_current_path = fs_current_path.parent_path();
        return 0;
    }else if(input == "/"){
        fs_current_path = fs_current_path.root_path();
        return 0;
    }else if(input == "~"){
        fs_current_path = current_user.home_dir;
        return 0;
    }else if(!exists(fs_current_path.append(input))){
        fs_current_path = if_fail;
        return 1;
    }
    return 0;
}

int cd(std::string input){
    while(true){
        if(cd_single(input.substr(0, input.find("/")))){
            std::cout << input << " is not a directory";
            return 1;
        }
        input = input.substr(input.find("/") + 1, input.length());
        if (input.find("/") == -1) {
            cd_single(input);
            break;
        }
    }
    return 0;
}

#endif