#ifndef CMD_LS_H__
#define CMD_LS_H__

#include <iostream>
#include <filesystem>

#include "../global_var.h"

using namespace std;
using namespace std::filesystem;

int ls(){
    if(!exists(fs_current_path)){
        return 1;
    }
    directory_iterator list(fs_current_path);
    for(auto& it : list){
        if(1/* file not start with . */){
            cout << it.path().filename() << "\t";
        }
    }
    return 0;
}

int la(){
    if(!exists(fs_current_path)){
        return 1;
    }
    directory_iterator list(fs_current_path);
    for(auto& it : list){
        cout << it.path().filename() << "\n";
    }
    return 0;
}

#endif