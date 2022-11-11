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
        if(it.path().filename().u8string()[0] != '.'){
            if(it.is_directory()){
                cout << theme["dir"] << it.path().filename().u8string() << reset;
                cout << "/";
            }else{
                cout << it.path().filename().u8string();
            }
            cout << "\t";
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
        cout << it.path().filename().u8string();
        if(it.is_directory()){
            cout << "/";
        }
        cout << "\n";
    }
    return 0;
}

#endif