#include "shell.h"

#include <string_view>

int Shell::cmd_clear(const std::vector<std::string>& arg, VariableManager& vars) {
    std::string_view sys = vars.get("SYSTEM");
    if (sys != "Linux" && sys != "MacOS" && sys != "Unix") {
        system("CLS");
    } else {
        system("clear");
    }
    return 0;
}
