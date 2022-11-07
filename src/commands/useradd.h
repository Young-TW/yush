#ifndef CMD_USERADD_H__
#define CMD_USERADD_H__

#include <iostream>
#include <string>
using namespace std;

#include "../user.cpp"
#include "../feature/rand_str_gen.h"

int useradd(){
    string name = string("guest_").append(gen_random(7));
    // User temp;
    // User_list.push_back(temp);
    // User Young = User(name);
    cout << "new user added, your user name is " << name;
    return 0;
}

int useradd(string name){
    // User Young = User(name);
    // User temp;
    // User_list.push_back(temp);
    cout << "new user added";
    return 0;
}

#endif