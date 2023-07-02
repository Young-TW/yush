#ifndef FEATURE_THEME_H
#define FEATURE_THEME_H

#include <map>

#include <fmt/color.h>

const std::map<std::string, fmt::v10::color> theme_default = {
    {"name", fmt::color::orange},
    {"path", fmt::color::purple},
    {"dir", fmt::color::cyan},
    {"warn", fmt::color::red},
    {"save", fmt::color::green},
};

#endif