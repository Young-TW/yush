#ifndef CMD_YUSH_H
#define CMD_YUSH_H

#include <iostream>
#include <string>
#include <filesystem>

#include "src/feature/yush_script.h"

int cmd::yush(){
    // new yush
    return 0;
}

int cmd::yush(std::filesystem::path target_script_file){
    return run_yush_script(target_script_file);
}

#endif