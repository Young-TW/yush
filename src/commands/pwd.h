#ifndef _CMD_PWD_H_
#define _CMD_PWD_H_

#include <iostream>
#include <filesystem>

#include "../global_var.h"

int yush::pwd(){
    std::cout << fs_current_path.u8string();
    return 0;
}

#endif