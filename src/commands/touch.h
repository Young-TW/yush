#ifndef _CMD_TOUCH_H_
#define _CMD_TOUCH_H_

#include <string>
#include <filesystem>
#include <fstream>

#include "src/global_var.h"

int yush::touch(std::string file){
    std::ifstream fin;
    std::ofstream fout;
    std::string file_path = fs_current_path.string() + "/" + file;
    fout.open(file_path);
    fout << "";
    fout.close();
    return 0;
}

#endif