#ifndef FEATURE_STRING_PARSER_H
#define FEATURE_STRING_PARSER_H

#include <vector>
#include <string>
#include <string_view>

std::vector<std::string> string_parser(std::string_view input, char flag) {
    std::vector<std::string> arg;
    for (std::size_t i = 0; i < input.size();) {
        std::size_t space = input.find(flag, i);
        if (space == std::string::npos) {
            space = input.size();
        }
        arg.emplace_back(input.substr(i, space-i));
        i = space + 1;
    }

    return arg;
}


#endif