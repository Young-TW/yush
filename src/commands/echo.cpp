#ifndef CMD_ECHO_H
#define CMD_ECHO_H

#include <vector>
#include <string_view>

#include "stream_manager.hpp"
#include "variable_manager.h"
#include "commands/cmds.h"

int cmd::echo(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager) {
    if (arg[1] == "$system") {
        stream_manager.out() << variable_manager.get("SYSTEM");
    } else if (arg[1] == "$theme") {
        stream_manager.out() << variable_manager.get("COLOR_THEME");
    } else {
        for (size_t i = 1; i < arg[1].size(); ++i) {
            stream_manager.out() << arg[1][i] << " ";
        }
    }
    return 0;
}

#endif