#ifndef _CMD_WHOAMI_H_
#define _CMD_WHOAMI_H_

#include <iostream>
#include <string>

int whoami(std::string user_name){
    std::cout << user_name;
    return 0;
}

#endif