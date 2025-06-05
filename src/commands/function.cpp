#include <iostream>
#include <vector>

#include "fmt/format.h"
#include "shell.h"

int Shell::cmd_function(const std::vector<std::string>& arg) {
    if (arg.size() < 3) {
        fmt::print(stderr, "Argument size error.\n");
        return 1;
    }

    std::string function_content;
    for (std::size_t i = 2; i < arg.size(); ++i) {
        function_content += arg[i];
        function_content += ' ';
    }

    if (!function_content.empty()) {
        function_content.pop_back();
    }

    this->functions.set(arg[1], function_content);

    return 0;
}
