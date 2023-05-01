#include <string>
#include <vector>

#include "feature/string_parser.h"

std::vector<std::string> string_parser(std::string_view input, char flag) {
    std::vector<std::string> arg;
    for (std::size_t i = 0; i < input.size();) {
        std::size_t space = input.find(flag, i);
        if (space == std::string::npos) {
            space = input.size();
        }
        arg.emplace_back(input.substr(i, space - i));
        i = space + 1;
    }

    return arg;
}