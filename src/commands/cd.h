#ifndef CMD_CD_H__
#define CMD_CD_H__

#include <iostream>
#include <string>
#include <filesystem>

#include "../global_var.h"

using namespace std;
using namespace std::filesystem;

int cd(string i){
    if(!exists(fs_current_path)){
        return 1;
    }
    if(i == ".."){
        fs_current_path = fs_current_path.parent_path();
    }else if(i == "/"){
        fs_current_path = fs_current_path.root_path();
    }else if(i == "~"){
        fs_current_path = User_list.at(current_user).home_dir;
    }else{
        fs_current_path = fs_current_path.append(i);
    }
    return 0;
}

#endif