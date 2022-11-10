#ifndef GLOBAL_VAR_H__
#define GLOBAL_VAR_H__

#include <string>
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
User young = User("young");
User sudo = User("sudo");
User virtual_user = User("virtual_user");
vector<User> User_list = {young, sudo, virtual_user};
User current_user = young;

#endif