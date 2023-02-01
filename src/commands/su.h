#ifndef CMD_SU_H
#define CMD_SU_H

#include "src/global_var.h"

int yush::su(){
    current_user = User("sudo");
    return 0;
}

int yush::su(User user){
    current_user = user;
    return 0;
}

#endif