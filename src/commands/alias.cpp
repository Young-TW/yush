#include <string>

#include "stream_manager.hpp"
#include "variable_manager.h"
#include "commands/cmds.h"

int cmd::alias(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager) {
    // add command
    size_t found = arg.at(1).find("=");
    std::string cmd_name = arg.at(1).substr(0, found);
    std::string cmd_content = arg.at(1).substr(found+1, arg.at(1).size()-1);
    // alias_map.insert(cmd_name, cmd_content);
    return 0;
}