#ifndef _CMD_UNKNOWN_H_
#define _CMD_UNKNOWN_H_

#include <iostream>

#include "src/global_var.h"

int yush::unknown(std::string cmd){
    std::cout << theme["warn"] << "Unknown command: " << reset << cmd;
    return 1;
}

#endif