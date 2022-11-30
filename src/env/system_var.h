#ifndef ENV_SYSTEM_VAR_H__
#define ENV_SYSTEM_VAR_H__

#include <string>

std::string system_parse(){
    std::string system = std::string("Unknown");

    #ifdef __WINDOWS__
        system = std::string("Windows");
    #elif _WIN32
        system = std::string("Windows 32");
    #elif __WIN64
        system = std::string("Windows 64");
    #elif __APPLE__
        system = std::string("Apple");
    #elif __unix__
        system = std::string("Unix");
    #elif __linux__
        system = std::string("Linux");
    #endif

    return system;
}

const std::string sys = system_parse();


#endif