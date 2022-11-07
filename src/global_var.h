#ifndef GLOBAL_VAR_H__
#define GLOBAL_VAR_H__

#include <string>
#include <map>
#include <vector>
#include <filesystem>
#include <string>

#include "./env/system.h"

using namespace std;
using namespace std::filesystem;

string input;
const string sys = system();
const string user_name = "Young";
bool exit_check = 0;
vector<string> parsed_cmd;
path fs_current_path("/Users/young");
vector<string> input_past;
int place_input_past = 0;

map<string, string> commands ={
    {"cat"   , "print content of file"},
    {"cd"    , "change current path"},
    {"clear" , "clear texts"},
    {"date"  , "display current date"},
    {"echo"  , "display texts or using $ to display varible"},
    {"exit"  , "exit shell"},
    {"help"  , "print all commands"},
    {"ls"    , "display file and directory in current path"},
    {"time"  , "display current time"},
    {"whoami", "print user name"},
};

#endif