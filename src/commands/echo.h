#ifndef CMD_ECHO_H__
#define CMD_ECHO_H__

#include <iostream>
#include <vector>
#include <string>

#include "../env/system_var.h"
#include "../global_var.h"

int echo(vector<string> i){
    if(i.at(1) == "$system"){
        std::cout << sys;
    }else{
        for(size_t j=1;j<i.size();j++){
            std::cout << i.at(j) << " ";
        }
    }
    return 0;
}

#endif