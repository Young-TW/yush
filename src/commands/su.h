#ifndef _CMD_SU_H_
#define _CMD_SU_H_

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