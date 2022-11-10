#ifndef CMD_SU_H__
#define CMD_SU_H__

#include <string>

#include "../user.cpp"
#include "../global_var.h"

using namespace std;

int su(){
    current_user = sudo;
    return 0;
}

int su(User user){
    current_user = user;
    return 0;
}

#endif