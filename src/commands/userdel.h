#ifndef _CMD_USERDEL_H_
#define _CMD_USERDEL_H_

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