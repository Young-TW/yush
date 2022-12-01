#ifndef _CMD_USERDEL_H_
#define _CMD_USERDEL_H_

#include <iostream>
#include <string>

#include "../global_var.h"

int userdel(){
    std::cout << "Please input user name.";
    return 1;
}

int userdel(std::string name){
    // User_list.erase(name);
    // ~User();
    return 0;
}

#endif