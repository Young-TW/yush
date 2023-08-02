#ifndef CMDS_H
#define CMDS_H

#include <filesystem>
#include <map>
#include <string>
#include <string_view>
#include <vector>
#include "variable_manager.h"

namespace cmds {
    int alias(const std::vector<std::string>& arg,VariableManager& vars);
    int cd(const std::vector<std::string>& arg,VariableManager& vars);
    int clear(const std::vector<std::string>& arg,VariableManager& vars);
    int echo(const std::vector<std::string>& arg,VariableManager& vars);
    int function(const std::vector<std::string>& arg,VariableManager& vars);
    int ls(const std::vector<std::string>& arg,VariableManager& vars);
    int pwd(const std::vector<std::string>& arg,VariableManager& vars);
    int set(const std::vector<std::string>& arg,VariableManager& vars);
}  // namespace cmds

#endif
