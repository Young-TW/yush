#ifndef CMD_USERADD_H__
#define CMD_USERADD_H__

#include <iostream>
#include <string>
using namespace std;

#include "../user.cpp"
#include "../feature/rand_str_gen.h"

int useradd(){
    string user_name = string("guest_").append(gen_random(7));
    User(user_name);
    return 0;
}

int useradd(string name){
    User(user_name);
    return 0;
}

#endif