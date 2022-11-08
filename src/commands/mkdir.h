#ifndef CMD_MKDIR_H__
#define CMD_MKDIR_H__

#include <iostream>
#include <string>
#include <filesystem>

#include "../global_var.h"

using namespace std;
using namespace std::filesystem;

int mkdir(){
    if(!exists(fs_current_path)){
        create_directories(fs_current_path);
        fs_current_path = fs_current_path.parent_path();
        return 0;
    }
    return 0;
}

int mkdir(string i){
    if(!exists(fs_current_path.append(i))){
        create_directories(fs_current_path);
        fs_current_path = fs_current_path.parent_path();
        return 0;
    }else{
        cout << "directory already exists";
    }
    return 0;
}

#endif