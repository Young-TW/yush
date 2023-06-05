#include "cmds.h"

#include <string_view>

int cmds::clear(const std::vector<std::string>& arg,
                StreamManager& stream_manager,
                VariableManager& variable_manager) {
    std::string_view sys = variable_manager.get("SYSTEM");
    if (sys != "Linux" && sys != "MacOS" && sys != "Unix") {
        system("CLS");
    } else {
        system("clear");
    }
    return 0;
}
