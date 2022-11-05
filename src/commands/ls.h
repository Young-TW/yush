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
        cout << it.path().filename() << endl;
    }
    return 0;
}

#endif