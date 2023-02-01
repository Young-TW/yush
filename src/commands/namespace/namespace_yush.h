#ifndef CMD_NAMESPACE_YUSH_H
#define CMD_NAMESPACE_YUSH_H

#include <string>
#include <vector>
#include <map>
#include <filesystem>

#include "../../global_var.h"

namespace yush{
    int alias(std::string input);
    int cat(std::string input);
    int cd_single(std::string input);
    int cd(std::string input);
    int clear();
    int date();
    int echo(std::vector<std::string> input);
    int exit();
    int help(std::map<std::string, std::string> commands);
    int ls();
    int la();
    int mkdir();
    int mkdir(std::string input);
    int pwd();
    int rm(std::string file);
    int rm(std::string arg,std::string dir);
    int su();
    int su(User user);
    int time();
    int touch(std::string file);
    int unknown(std::string cmd);
    int useradd();
    int useradd(std::string name);
    int userdel();
    int userdel(std::string name);
    int whoami(std::string user_name);
    int yush();
    int yush(std::filesystem::path target_script_file);
}

#endif