#ifndef CMD_ECHO_H
#define CMD_ECHO_H

#include <iostream>
#include <vector>
#include <string>

#include "src/env/system_var.h"
#include "src/global_var.h"

int yush::echo(std::vector<std::string> input){
    if(input.at(1) == "$system"){
        std::cout << sys;
    }else{
        for(size_t i=1;i<input.size();i++){
            std::cout << input.at(i) << " ";
        }
    }
    return 0;
}

#endif