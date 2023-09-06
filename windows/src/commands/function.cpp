#include "shell.h"

#include <iostream>
#include <string_view>
#include <unordered_map>
#include <vector>

int Shell::cmd_function(const std::vector<std::string>& arg) {
    std::string function_content;
    for (std::size_t i = 2; i < arg.size(); ++i) {
        function_content += arg[i];
        function_content += ' ';
    }

    function_content.pop_back();

    this->functions.set(arg[1], function_content);

    return 0;
}
