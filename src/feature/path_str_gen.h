#ifndef FEATURE_PATH_STR_GEN_H
#define FEATURE_PATH_STR_GEN_H

#include <string>
#include <iostream>

std::string path_str_gen(std::string_view pwd, std::string_view home_dir){
    std::string path = "~";
    for(int i=0;i<home_dir.length();i++){
        if(home_dir.at(i) != pwd[i]){
            path = pwd;
            return path;
        }
    }

    std::string temp = "";
    temp = pwd.substr(home_dir.length(), pwd.length()-1);
    path.append(temp);
    return path;
}

#endif