#ifndef CMD_CD_H__
#define CMD_CD_H__

#include <iostream>
#include <string>
#include <filesystem>

#include "../global_var.h"

using namespace std;
using namespace std::filesystem;

int cd_single(string i){
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

int cd(string input){
    while(true){
        cd_single(input.substr(0, input.find("/")));
        input = input.substr(input.find("/") + 1, input.length());
        if (input.find("/") == -1) {
            cd_single(input);
            break;
        }
    }
    return 0;
}

#endif