#include "cmds.h"

#include <string_view>

int cmds::whoami(const std::vector<std::string>& arg,
                 StreamManager& stream_manager,
                 VariableManager& variable_manager) {
    stream_manager.out() << variable_manager.get("USER") << "\n";
    return 0;
}
