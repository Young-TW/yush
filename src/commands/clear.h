#ifndef CMD_CLEAR_H__
#define CMD_CLEAR_H__

#include <iostream>

#include "../env/system_var.h"

using namespace std;

int clear(){
    if(sys != "Linux" && sys != "Apple" && sys != "Unix"){
        system("CLS");
    }else{
        system("clear");
    }
    return 0;
}

#endif