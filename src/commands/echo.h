#ifndef _CMD_ECHO_H_
#define _CMD_ECHO_H_

#include <iostream>
#include <vector>
#include <string>

#include "../env/system_var.h"
#include "../global_var.h"

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