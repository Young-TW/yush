#ifndef CMD_CAT_H
#define CMD_CAT_H

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

#include "src/global_var.h"

int yush::cat(std::string input){
    std::ifstream fin;
    std::ofstream fout;
    if(!exists(fs_current_path)){
        return 1;
    }
    std::filesystem::path target_file = fs_current_path.append(input);
    fin.open(target_file);
    std::string temp;
    while(!fin.eof()){
        fin >> temp;
        std::cout << temp << " ";
    }
    return 0;
}

#endif