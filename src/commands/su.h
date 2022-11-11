#ifndef CMD_SU_H__
#define CMD_SU_H__

#include "../global_var.h"

int su(){
    current_user = User("sudo");
    return 0;
}

int su(User user){
    current_user = user;
    return 0;
}

#endif