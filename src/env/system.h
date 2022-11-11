#ifndef ENV_SYSTEM_H__
#define ENV_SYSTEM_H__

#include <string>

#include "../global_var.h"

using namespace std;

string system(){
    string system = string("Unknown");

    #ifdef __WINDOWS__
        system = string("Windows");
    #elif _WIN32
        system = string("Windows 32");
    #elif __WIN64
        system = string("Windows 64");
    #elif __APPLE__
        system = string("Apple");
    #elif __unix__
        system = string("Unix");
    #elif __linux__
        system = string("Linux");
    #endif

    return system;
}

#endif