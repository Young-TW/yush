#include <fstream>
#include <iostream>
#include <filesystem>
#include <cxxopts.hpp>
#include "shell.h"

int main(int argc, char *argv[]) {
    cxxopts::Options options("shell", "Young's shell");

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
        std::cout << options.help() << std::endl;
        return 0;
    }

    if (result.count("version")) {
        std::cout << "yush, version 0.3.3" << std::endl;
        return 0;
    }

    if (result.count("debug-output")) {
        std::ofstream fout(result["debug-output"].as<std::filesystem::path>());
        return Shell(std::cin, std::cout, fout).run(false);
    }

    if (result.count("script")) {
        std::ifstream fin(result["script"].as<std::filesystem::path>());
        return Shell(fin, std::cout, std::cerr).run(false);
    }

    return Shell(std::cin, std::cout, std::cerr).run(true /*result.count("interactive")*/);
}
