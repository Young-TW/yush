#ifndef GLOBAL_VAR_H__
#define GLOBAL_VAR_H__

#include <string>
#include <map>
#include <vector>
using namespace std;

const string user_name = "Young";
bool exit_check = 0;
vector<string> parsed_cmd;

map<string, string> commands ={
    {"clear", "clear texts"},
    {"echo", "display texts"},
    {"exit", "exit shell"},
    {"help", "print all commands"},
    {"whoami", "print user name"},
};

#endif