#include <iostream>
#include <string_view>

#include "shell.h"
#include "commands/cmds.h"
#include "feature/theme.h"

Shell::Shell(std::istream& is)
    : exit_check(false)
    , is(is)
{
    variables = {
        {"PWD", std::filesystem::current_path().lexically_normal().string()},
        {"USER", "young"},
        {"COLOR_NAME", yellow},
        {"COLOR_PATH", magenta},
        {"COLOR_DIR", cyan},
        {"COLOR_WARN", red},
        {"COLOR_SAVE", green},
        {"COLOR_RESET", reset},
        {"SYSTEM", sys},
    };
}

int Shell::run() {
    int runtime_status = 0;
    while (!exit_check && is) {
        std::cout << "\n\n" << variables.at("COLOR_NAME") << variables.at("USER") << reset
                  << ' ' << variables.at("COLOR_PATH") << variables.at("PWD") << reset;
        if (runtime_status == 1) {
            std::cout << variables.at("COLOR_WARN");
        }
        std::cout << '\n' << runtime_status << "> " << reset;

        std::string input;
        getline(is, input);

        runtime_status = run_command(parse_command(input), std::cin, std::cout);
    }
    return runtime_status;
}

std::vector<std::string> Shell::parse_command(std::string_view input) {
    std::vector<std::string> arg;
    for (size_t i = 0; i < input.size();) {
        auto space = input.find(' ', i);
        if (space == std::string::npos) {
            space = input.size();
        }
        arg.push_back(std::string(input.substr(i, space)));
        i = space + 1;
    }
    return arg;
}

int Shell::run_command(const std::vector<std::string>& arg, std::istream& is, std::ostream& os) {
    using namespace cmd;

    std::string_view command = arg[0];

    if (command == "alias") {
        return alias(arg, is, os, variables);
    } else if (command == "cat") {
        return cat(arg, is, os, variables);
    } else if (command == "cd") {
        return cd(arg, is, os, variables);
    } else if (command == "clear") {
        return clear(arg, is, os, variables);
    } else if (command == "date") {
        return date(arg, is, os, variables);
    } else if (command == "echo") {
        return echo(arg, is, os, variables);
    } else if (command == "exit") {
        return exit(arg, is, os, variables);
    } else if (command == "help") {
        return help(arg, is, os, variables);
    } else if (command == "la") {
        return la(arg, is, os, variables);
    } else if (command == "ls") {
        return ls(arg, is, os, variables);
    } else if (command == "mkdir") {
        return mkdir(arg, is, os, variables);
    } else if (command == "pwd") {
        return pwd(arg, is, os, variables);
    } else if (command == "rm") {
        return rm(arg, is, os, variables);
    } else if (command == "time") {
        return time(arg, is, os, variables);
    } else if (command == "touch") {
        return touch(arg, is, os, variables);
    } else if (command == "whoami") {
        return whoami(arg, is, os, variables);
    } else if (command == "yush") {
        return yush(arg, is, os, variables);
    } else {
        return 127;
    }
}

int Shell::exit(const std::vector<std::string>& arg, std::istream& is, std::ostream& os, std::map<std::string, std::string>& variables) {
    exit_check = true;
    return 0;
}