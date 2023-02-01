#ifndef CMD_TOUCH_H
#define CMD_TOUCH_H

#include <string>
#include <filesystem>
#include <fstream>

#include "src/global_var.h"

int cmd::touch(std::string file){
    std::ifstream fin;
    std::ofstream fout;
    std::string file_path = fs_current_path.string() + "/" + file;
    fout.open(file_path);
    fout << "";
    fout.close();
    return 0;
}

#endif