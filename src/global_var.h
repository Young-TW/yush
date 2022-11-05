#ifndef GLOBAL_VAR_H__
#define GLOBAL_VAR_H__

#include <string>
#include <map>
#include <vector>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

const string user_name = "Young";
bool exit_check = 0;
vector<string> parsed_cmd;
path fs_current_path("/Users/young");

map<string, string> commands ={
    {"clear", "clear texts"},
    {"date", "display current date"},
    {"echo", "display texts"},
    {"exit", "exit shell"},
    {"help", "print all commands"},
    {"time", "display current time"},
    {"whoami", "print user name"},
};

#endif