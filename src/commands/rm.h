#ifndef CMD_RM_H__
#define CMD_RM_H__

#include <string>
#include <filesystem>

#include "../global_var.h"

using namespace std;
using namespace std::filesystem;

int rm(string arg,string dir){
    if(arg == "-rf"){
        // remove(fs_current_path.u8string() + dir);
        return 0;
    }else{
        cout << "Unknown argument";
        return 1;
    }
    return 0;
}

int rm(string file){
    // remove(fs_current_path.u8string() + file);
    return 0;
}

#endif