#ifndef _CMD_ECHO_H_
#define _CMD_ECHO_H_

#include <iostream>
#include <vector>
#include <string>

#include "../env/system_var.h"
#include "../global_var.h"

int echo(std::vector<std::string> i){
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