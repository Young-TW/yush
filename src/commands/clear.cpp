#include "cmds.h"

#include <string_view>

int cmds::clear(const std::vector<std::string>& arg,
                StreamManager& stream,
                VariableManager& vars) {
    std::string_view sys = vars.get("SYSTEM");
    if (sys != "Linux" && sys != "MacOS" && sys != "Unix") {
        system("CLS");
    } else {
        system("clear");
    }
    return 0;
}
