#ifndef FEATURE_STRING_PARSER_H
#define FEATURE_STRING_PARSER_H

#include <vector>
#include <string>
#include <string_view>

std::vector<std::string> string_parser(std::string_view input, char flag);

#endif