#ifndef CMD_PWD_H
#define CMD_PWD_H

#include <iostream>
#include <filesystem>

#include "src/global_var.h"

int yush::pwd(){
    std::cout << fs_current_path.string();
    return 0;
}

#endif