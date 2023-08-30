#include "shell.h"

#include <iostream>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <fmt/format.h>

std::unordered_map<std::string, std::vector<std::string>> functions;

std::vector<std::string> parse(std::string_view input) {
    std::vector<std::string> arg;
    for (std::size_t i = 0; i < input.size();) {
        std::size_t space = input.find(' ', i);
        if (space == std::string::npos) {
            space = input.size();
        }
        arg.emplace_back(input.substr(i, space - i));
        i = space + 1;
    }
    return arg;
}

int Shell::cmd_function(const std::vector<std::string>& arg, VariableManager& vars) {
    if (arg.size() != 2 && arg.size() != 3) {
        fmt::print(stderr, "Argument size error.\n");
        return 1;
    }

    if (arg.size() == 2) {
        // run function
        // auto func = functions.find(arg[1]);
        // while (str_temp.back() == '\\') {

        // }

        return 0;
    }

    std::vector<std::string> func_temp;
    std::string str_temp;
    func_temp.clear();
    str_temp = arg.back();
    while (str_temp.back() == '\\') {  // record function
        getline(std::cin, str_temp);
        func_temp.push_back(str_temp);
    }

    functions.insert(std::pair(arg[1], func_temp));

    return 0;
}
