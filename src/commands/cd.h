#ifndef CMD_CD_H__
#define CMD_CD_H__

#include <iostream>
#include <string>
#include <filesystem>

#include "../global_var.h"

using namespace std;
using namespace std::filesystem;

int cd(string i){
    path if_fail = fs_current_path;
    if(i == ".."){
        fs_current_path = fs_current_path.parent_path();
    }else if(i == "/"){
        fs_current_path = fs_current_path.root_path();
    }else if(i == "~"){
        fs_current_path = current_user.home_dir;
    }else if(!exists(fs_current_path.append(i))){
        cout << i << " is not a directory";
        fs_current_path = if_fail;
        return 1;
    }
    return 0;
}

#endif