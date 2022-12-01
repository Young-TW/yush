#ifndef _GLOBAL_VAR_H_
#define _GLOBAL_VAR_H_

#include <string>
#include <vector>
#include <filesystem>

#include "./user.h"
#include "./feature/theme.h"

std::string input;
bool exit_check = 0;
std::vector<std::string> parsed_cmd;
std::filesystem::path fs_current_path;
std::vector<std::string> input_past;
size_t place_input_past = 0;
const User young = User("young");
const User sudo = User("sudo");
const User virtual_user = User("virtual_user");
std::vector<User> User_list = {young, sudo, virtual_user};
User current_user = young;
std::map<std::string, std::string> theme = theme_defalut;
std::map<std::string, std::string> alias_map;

#endif