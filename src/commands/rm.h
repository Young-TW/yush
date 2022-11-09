#ifndef CMD_RM_H__
#define CMD_RM_H__

#include <string>
#include <filesystem>

#include "../global_var.h"

using namespace std;
using namespace std::filesystem;

int rm(string file,string dir){
    if(file == "-rf"){
        //remove dir
        remove(dir);
        return 0;
    }else{
        //remove file
        remove(file);
    }
    return 0;
}

#endif