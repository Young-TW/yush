#ifndef CMD_UNKNOWN_H__
#define CMD_UNKNOWN_H__

#include <iostream>

#include "../global_var.h"

int unknown(string cmd){
    std::cout << theme["warn"] << "Unknown command: " << reset << cmd;
    return 1;
}

#endif