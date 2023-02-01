#ifndef CMD_CLEAR_H
#define CMD_CLEAR_H

#include <iostream>

#include "src/env/system_var.h"

int yush::clear(){
    if(sys != "Linux" && sys != "Apple" && sys != "Unix"){
        system("CLS");
    }else{
        system("clear");
    }
    return 0;
}

#endif