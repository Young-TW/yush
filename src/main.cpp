#include <fstream>
#include <filesystem>
#include <cxxopts.hpp>

#include <fmt/format.h>

#include "shell.h"

int main(int argc, char *argv[]) {
    cxxopts::Options options("yush", "Young's shell");

    options.add_options()
        ("script"        , "input script file"                    , cxxopts::value<std::filesystem::path>())
        ("o,debug-output", "Enable debug message output to a file", cxxopts::value<std::filesystem::path>())
        ("h,help"        , "Print help message and exit"          , cxxopts::value<bool>()->default_value("false"))
        ("c,command"     , "Execute single command"               , cxxopts::value<std::string>())
        // ("i,interactive" , "Is interactive mode"                  , cxxopts::value<bool>()->default_value("true"))
        ("v,version"     , "Print version and exit"               , cxxopts::value<bool>()->default_value("false"))
        ;

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        fmt::print("{}", options.help());
        return 0;
    }

    if (result.count("version")) {
        fmt::print("yush, version 0.4.2\n");
        return 0;
    }

    // if (result.count("debug-output")) {
    //     std::ofstream fout(result["debug-output"].as<std::filesystem::path>());
    //     return Shell().run(false);
    // }

    if (result.count("script")) {
        std::ifstream fin(result["script"].as<std::filesystem::path>());
        return Shell().run(true);
    }

    return Shell().run(true);
}
