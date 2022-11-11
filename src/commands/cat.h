#ifndef CMD_CAT_H__
#define CMD_CAT_H__

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

#include "../global_var.h"

using namespace std;
using namespace std::filesystem;

ifstream fin;
ofstream fout;

int cat(string i){
    if(!exists(fs_current_path)){
        return 1;
    }
    path target_file = fs_current_path.append(i);
    fin.open(target_file);
    string temp;
    while(!fin.eof()){
        fin >> temp;
        cout << temp << " ";
    }
    return 0;
}

#endif