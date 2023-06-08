#include "cmds.h"

#include <string_view>
#include <vector>

int cmds::echo(const std::vector<std::string>& arg,
               StreamManager& stream,
               VariableManager& vars) {
    if (arg[1][0] == '$') {
        if (vars.exist(arg[1].substr(1, arg[1].size() - 1))) {
            stream.out()
                << vars.get(arg[1].substr(1, arg[1].size() - 1))
                << "\n";
            return 0;
        }
        stream.err() << "Variable not found\n";
        return 1;
    }

    for (size_t i = 1; i < arg.size(); i++) {
        stream.out() << arg[i] << " ";
    }

    stream.out() << "\n";
    return 0;
}
