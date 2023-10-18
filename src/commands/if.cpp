#include "shell.h"

#include <vector>
#include <string>

#include <fmt/core.h>

int Shell::cmd_if(const std::vector<std::string>& arg) {
    if (arg.size() < 4) {
        std::cerr << "if: not enough arguments" << std::endl;
        return 1;
    }



    return 0;
}
