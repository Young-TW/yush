#include "shell.h"

#include <iostream>
#include <filesystem>

#include <fmt/format.h>
#include <fmt/color.h>

int Shell::cmd_ls(const std::vector<std::string>& arg) {
    if (!std::filesystem::exists(std::filesystem::current_path())) {
        fmt::print(stderr, "This directory is not exists.\n");
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
