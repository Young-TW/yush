#include "cmds.h"

#include <iostream>
#include <filesystem>

#include <fmt/format.h>
#include <fmt/color.h>

int cmds::ls(const std::vector<std::string>& arg, VariableManager& vars) {
    if (!std::filesystem::exists(std::filesystem::current_path())) {
        std::cerr << "This directory is not exists.\n";
        return 1;
    }

    std::filesystem::directory_iterator list(std::filesystem::current_path());
    for (auto& it : list) {
        if (it.path().filename().string()[0] != '.') {
            if (it.is_directory()) {
                fmt::print(fg(fmt::color::cyan), "{}", it.path().filename().string());
                fmt::print("/");
            } else {
                fmt::print(fg(fmt::color::white), "{}", it.path().filename().string());
            }

            fmt::print("\t");
        }
    }

    fmt::print("\n");
    return 0;
}
