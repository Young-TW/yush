#include <filesystem>
#include <iostream>

#include "fmt/color.h"
#include "fmt/format.h"

#include "shell.h"

int Shell::cmd_ls(const std::vector<std::string>& arg) {
    // parse arguments if path parameters are given
    if (arg.size() > 1) {
        for (size_t i = 1; i < arg.size(); ++i) {
            if (!std::filesystem::exists(arg[i])) {
                fmt::print(stderr, "Path '{}' does not exist.\n", arg[i]);
                return 1;
            }

            fmt::print("Listing directory: {}\n", arg[i]);
            for (const auto& entry : std::filesystem::directory_iterator(arg[i])) {
                if (entry.path().filename().string()[0] != '.') {
                    if (entry.is_directory()) {
                        fmt::print(fg(fmt::color::cyan), "{}", entry.path().filename().string());
                        fmt::print("/");
                    } else {
                        fmt::print(fg(fmt::color::white), "{}", entry.path().filename().string());
                    }
                    fmt::print("\t");
                }
            }

            fmt::print("\n");
        }
        return 0;
    }

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
