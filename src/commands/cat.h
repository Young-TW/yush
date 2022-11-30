#ifndef CMD_CAT_H__
#define CMD_CAT_H__

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

#include "../global_var.h"

std::ifstream fin;
std::ofstream fout;

int cat(std::string input){
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