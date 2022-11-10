#ifndef CMD_UNKNOWN_H__
#define CMD_UNKNOWN_H__

#include <iostream>

#include "../feature/color_text.h"

using namespace std;

int unknown(string cmd){
    cout << red << "Unknown command: " << reset << cmd;
    return 1;
}

#endif