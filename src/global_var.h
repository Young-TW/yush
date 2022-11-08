#ifndef GLOBAL_VAR_H__
#define GLOBAL_VAR_H__

#include <string>
#include <map>
#include <vector>
#include <filesystem>

#include "./env/system.h"
#include "./user.cpp"

using namespace std;
using namespace std::filesystem;

string input;
// const string sys = system();
bool exit_check = 0;
vector<string> parsed_cmd;
path fs_current_path;
vector<string> input_past;
int place_input_past = 0;
User Young = User("Young");
vector<User> User_list = {Young};
int current_user = 0;

map<string, string> commands ={
    {"cat"    , "print content of file"},
    {"cd"     , "change current path"},
    {"clear"  , "clear texts"},
    {"date"   , "display current date"},
    {"echo"   , "display texts or using $ to display varible"},
    {"exit"   , "exit shell"},
    {"help"   , "print all commands"},
    {"ls"     , "display file and directory in current path"},
    {"pwd"    , "display current path"},
    {"su"     , "switch to another user"},
    {"time"   , "display current time"},
    {"useradd", "add another user"},
    {"userdel", "delete selected user"},
    {"whoami" , "print user name"},
};

#endif