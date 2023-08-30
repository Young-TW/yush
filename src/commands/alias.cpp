#include "shell.h"

#include <string>

int Shell::cmd_alias(const std::vector<std::string>& arg, VariableManager& vars) {
    // add command
    size_t found = arg.at(1).find("=");
    std::string cmd_name = arg.at(1).substr(0, found);
    std::string cmd_content = arg.at(1).substr(found + 1, arg.at(1).size() - 1);
    // alias_map.insert(cmd_name, cmd_content);
    return 0;
}
