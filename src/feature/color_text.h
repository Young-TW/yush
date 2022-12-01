#ifndef _FEATURE_COLOR_TEXT_H_
#define _FEATURE_COLOR_TEXT_H_

#include <string>

const std::string black("\033[0;30m");
const std::string red("\033[0;31m");
const std::string green("\033[1;32m");
const std::string yellow("\033[1;33m");
const std::string blue("\033[0;34m");
const std::string magenta("\033[0;35m");
const std::string cyan("\033[0;36m");
const std::string gray("\033[0;37m");
const std::string dark_gray("\033[0;90m");
const std::string light_red("\033[0;91m");
const std::string light_green("\033[0;92m");
const std::string light_blue("\033[0;93m");
const std::string light_magenta("\033[0;95m");
const std::string light_cyan("\033[0;96m");
const std::string white("\033[0;97m");

const std::string black_back("\033[;40m");
const std::string red_back("\033[0;41m");
const std::string green_back("\033[1;42m");
const std::string yellow_back("\033[1;43m");
const std::string magenta_back("\033[0;45m");
const std::string cyan_back("\033[0;46m");
const std::string white_back("\033[0;47m");

const std::string reset("\033[0m");

#endif