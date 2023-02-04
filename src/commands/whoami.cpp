#ifndef CMD_WHOAMI_H
#define CMD_WHOAMI_H

#include <string_view>

#include "stream_manager.hpp"
#include "variable_manager.h"
#include "commands/cmds.h"

int cmd::whoami(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager){
    stream_manager.out() << variable_manager.get("USER");
    return 0;
}

#endif