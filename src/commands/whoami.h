#ifndef CMD_WHOAMI_H
#define CMD_WHOAMI_H

#include <iostream>
#include <string>

int yush::whoami(std::string user_name){
    std::cout << user_name;
    return 0;
}

#endif