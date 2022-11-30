#ifndef _YUSH_SCRIPT_H_
#define _YUSH_SCRIPT_H_

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>
#include <codecvt>

int run_yush_script(std::filesystem::path target_script_file){
    std::ifstream fin;
    std::ofstream fout;
    fin.open(target_script_file);
    exit_check = 0;
    int runtime_status=0;
    while(exit_check == 0 && getline(fin, input)){
        // std::codecvt_utf8<wchar_t>;
        parse_command(input);
        runtime_status = call_function(parsed_cmd);
    }
    return exit_check;
}

/*
std::wstring readFile(std::string filename)
{
    std::wifstream wfin(filename);
    wfin.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
    std::wstringstream wss;
    wss << wfin.rdbuf();
    return wss.str();
}
*/

#endif