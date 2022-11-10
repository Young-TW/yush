#ifndef COLOR_TEXT_H__
#define COLOR_TEXT_H__

#include <string>

using namespace std;

const string black("\033[0;30m");
const string red("\033[0;31m");
const string green("\033[1;32m");
const string yellow("\033[1;33m");
const string magenta("\033[0;35m");
const string cyan("\033[0;36m");
const string white("\033[0;37m");

const string black_back("\033[;40m");
const string red_back("\033[0;41m");
const string green_back("\033[1;42m");
const string yellow_back("\033[1;43m");
const string magenta_back("\033[0;45m");
const string cyan_back("\033[0;46m");
const string white_back("\033[0;47m");

const string reset("\033[0m");

#endif