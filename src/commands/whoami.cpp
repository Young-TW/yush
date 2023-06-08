#include "cmds.h"

#include <string_view>

int cmds::whoami(const std::vector<std::string>& arg,
                 StreamManager& stream,
                 VariableManager& vars) {
    stream.out() << vars.get("USER") << "\n";
    return 0;
}
