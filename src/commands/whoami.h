#ifndef CMD_WHOAMI_H__
#define CMD_WHOAMI_H__

#include <iostream>
#include <string>

int whoami(std::string user_name){
    std::cout << user_name;
    return 0;
}

#endif