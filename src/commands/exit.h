#ifndef _CMD_EXIT_H_
#define _CMD_EXIT_H_

#include "src/global_var.h"

int yush::exit(){
    exit_check = 1;
    return 0;
}

#endif