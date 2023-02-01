#ifndef CMD_UNKNOWN_H
#define CMD_UNKNOWN_H

#include <iostream>

#include "src/global_var.h"

int cmd::unknown(std::string cmd){
    std::cout << theme["warn"] << "Unknown command: " << reset << cmd;
    return 1;
}

#endif