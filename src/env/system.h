#ifndef ENV_SYSTEM_H__
#define ENV_SYSTEM_H__

#include <string>

#include "../global_var.h"

using namespace std;

string system(){
    #ifdef __WINDOWS__
        string system = "Windows";
    #elif __WIN64
        string system = "Windows 64";
    #elif __WIN32
        string system = "Windows 32\n";
    #elif __APPLE__
        string system = "Apple";
    #elif __unix__
        string system = "Unux";
    #elif __linux__
        string system = "Linux";
    #elif
        string system = "Other";
    #endif

    return system;
}

#endif