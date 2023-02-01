#ifndef CMD_USERDEL_H
#define CMD_USERDEL_H

#include <iostream>
#include <string>

#include "src/global_var.h"

int cmd::userdel(){
    std::cout << "Please input user name.";
    return 1;
}

int cmd::userdel(std::string name){
    // User_list.erase(name);
    // ~User();
    return 0;
}

#endif