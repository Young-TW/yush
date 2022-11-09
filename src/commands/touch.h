#ifndef CMD_TOUCH_H__
#define CMD_TOUCH_H__

#include <string>
#include <filesystem>
#include <fstream>

#include "../global_var.h"

using namespace std;
using namespace std::filesystem;

int touch(string file){
    ofstream fout;
    string file_path = fs_current_path.u8string() + "/" +file;
    fout.open(file_path);
    fout << "";
    fout.close();
    return 0;
}

#endif