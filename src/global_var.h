#ifndef GLOBAL_VAR_H__
#define GLOBAL_VAR_H__

#include <string>
#include <vector>
#include <filesystem>

#include "./env/system.h"
#include "./user.h"
#include "./feature/theme.h"

using namespace std;
using namespace std::filesystem;

string input;
bool exit_check = 0;
vector<string> parsed_cmd;
path fs_current_path;
vector<string> input_past;
int place_input_past = 0;
User young = User("young");
const User sudo = User("sudo");
const User virtual_user = User("virtual_user");
vector<User> User_list = {young, sudo, virtual_user};
User current_user = young;
map theme = theme_defalut;
map<string, string> alias_map;

#endif