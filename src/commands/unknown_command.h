#ifndef CMD_UNKNOWN_H__
#define CMD_UNKNOWN_H__

#include <iostream>

#include "../feature/color_text.h"
#include "../feature/theme.h"

using namespace std;

int unknown(string cmd){
    cout << theme_def["warn_color"] << "Unknown command: " << reset << cmd;
    return 1;
}

#endif