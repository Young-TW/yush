#include <vector>
#include <string_view>

#include "stream_manager.hpp"
#include "variable_manager.h"
#include "cmds.h"

int cmd::echo(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager) {
    if (arg[1][0] == '$') {
        if (variable_manager.exist(arg[1].substr(1, arg[1].size()-1))) {
            stream_manager.out() << variable_manager.get(arg[1].substr(1, arg[1].size()-1));
            return 0;
        }
        stream_manager.err() << "Variable not found";
        return 1;
    }

    for (size_t i = 1; i < arg.size(); i++) {
        stream_manager.out() << arg[i] << " ";
    }

    return 0;
}