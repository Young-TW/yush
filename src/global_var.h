#ifndef GLOBAL_VAR_H__
#define GLOBAL_VAR_H__

#include <string>
#include <map>
using namespace std;

const string userName = "Young";
bool exit_check = 0;

map<string, string> commands ={
    {"exit", "exit shell."},
    {"help", "print all commands."},
    {"whoami", "print user name."},
    {"clear", "clear texts."},
};

#endif