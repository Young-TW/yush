#include <vector>
#include <string_view>

#include "stream_manager.hpp"
#include "variable_manager.h"
#include "cmds.h"

std::vector<std::vector<std::string>> functions;

std::vector<std::string> parse(std::string_view input){
    std::vector<std::string> arg;
    for (std::size_t i = 0; i < input.size();) {
        std::size_t space = input.find(' ', i);
        if (space == std::string::npos) {
            space = input.size();
        }
        arg.emplace_back(input.substr(i, space-i));
        i = space + 1;
    }
    return arg;
}

std::vector<std::string> func_temp;

int cmd::function(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager) {
    if (arg.size() != 2 && arg.size() != 3) {
        stream_manager.err() << "Argument size error.\n";
        return 1;
    }

    if (arg.size() == 2) {
        // run function
        return 0;
    }

    std::string str_temp;
    func_temp.clear();
    func_temp.push_back(arg[1]);
    str_temp = arg.back();
    while (str_temp.back() == '\\') { // record function
        getline(stream_manager.in(), str_temp);
        func_temp.push_back(str_temp);
    }

    functions.push_back(func_temp);

    return 0;
}