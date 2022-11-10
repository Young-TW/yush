#ifndef THEME_H__
#define THEME_H__

#include <iostream>
#include <filesystem>
#include <map>

#include "../global_var.h"
#include "./color_text.h"

using namespace std;
using namespace std::filesystem;

map<string, string> theme_def{
    {"name_color", yellow},
    {"path_color", magenta},
    {"warn_color", red},
};

#endif