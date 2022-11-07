#ifndef CMD_PWD_H__
#define CMD_PWD_H__

#include <iostream>
#include <filesystem>

#include "../global_var.h"

using namespace std;
using namespace std::filesystem;

int pwd(){
    cout << fs_current_path.u8string();
    return 0;
}

#endif