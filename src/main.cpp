#include <fmt/format.h>

#include <cxxopts.hpp>
#include <filesystem>
#include <fstream>

#include "shell.h"

int main(int argc, char *argv[]) {
    cxxopts::Options options("yush", "Young's shell");

    options.allow_unrecognised_options();

    options.add_options()("o,debug-output",
                          "Enable debug message output to a file",
                          cxxopts::value<std::filesystem::path>())(
        "h,help", "Print help message and exit",
        cxxopts::value<bool>()->default_value("false"))(
        "c,command", "Execute single command", cxxopts::value<std::string>())(
        "i,interactive", "Is interactive mode",
        cxxopts::value<bool>()->default_value("true"))(
        "v,version", "Print version and exit",
        cxxopts::value<bool>()->default_value("false"));

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        fmt::print("{}", options.help());
        return 0;
    }

    if (result.count("version")) {
        fmt::print("yush, version {}\n", YUSH_VERSION);
        return 0;
    }

    if (result.count("command")) {
        Command command;
        command.assign(result["command"].as<std::string>());
        command.parse();
        return shell.exec_cmd(command);
    }

    if (result.unmatched().size() > 0) {
        return Shell().run(result.unmatched().at(0));
    }

    return shell.run(result);
}
