#ifndef CMD_USERADD_H
#define CMD_USERADD_H

#include <iostream>
#include <string>

#include "src/user.h"
#include "src/feature/rand_str_gen.h"

int cmd::useradd(){
    std::string name = std::string("guest_").append(gen_random(7));
    // User temp;
    // User_list.push_back(temp);
    // User Young = User(name);
    std::cout << "new user added, your user name is " << name;
    return 0;
}

int cmd::useradd(std::string name){
    // User Young = User(name);
    // User temp;
    // User_list.push_back(temp);
    std::cout << "new user added";
    return 0;
}

#endif