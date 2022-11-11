#ifndef CMD_PWD_H__
#define CMD_PWD_H__

#include <iostream>
#include <filesystem>

#include "../global_var.h"

int pwd(){
    std::cout << fs_current_path.u8string();
    return 0;
}

#endif