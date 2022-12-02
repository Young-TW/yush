#ifndef _CMD_CLEAR_H_
#define _CMD_CLEAR_H_

#include <iostream>

#include "../env/system_var.h"

int yush::clear(){
    if(sys != "Linux" && sys != "Apple" && sys != "Unix"){
        system("CLS");
    }else{
        system("clear");
    }
    return 0;
}

#endif