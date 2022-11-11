#ifndef CMD_UNKNOWN_H__
#define CMD_UNKNOWN_H__

#include <iostream>

#include "../global_var.h"

using namespace std;

int unknown(string cmd){
    cout << theme["warn"] << "Unknown command: " << reset << cmd;
    return 1;
}

#endif