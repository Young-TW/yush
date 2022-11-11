#ifndef CMD_USERDEL_H__
#define CMD_USERDEL_H__

#include <iostream>
#include <string>

#include "../global_var.h"

using namespace std;

int userdel(){
    cout << "Please input user name.";
    return 1;
}

int userdel(string name){
    // User_list.erase(name);
    // ~User();
    return 0;
}

#endif