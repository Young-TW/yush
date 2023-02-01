#ifndef CMD_EXIT_H
#define CMD_EXIT_H

#include "src/global_var.h"

int yush::exit(){
    exit_check = 1;
    return 0;
}

#endif