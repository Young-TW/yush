#ifndef CMD_USERDEL_H
#define CMD_USERDEL_H

#include <iostream>
#include <string>

#include "src/global_var.h"

int yush::userdel(){
    std::cout << "Please input user name.";
    return 1;
}

int yush::userdel(std::string name){
    // User_list.erase(name);
    // ~User();
    return 0;
}

#endif