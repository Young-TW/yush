#include <iostream>
#include <string_view>
#include <fstream>

#include "stream_manager.hpp"
#include "variable_manager.h"
#include "shell.h"
#include "commands/cmds.h"
#include "env/user.h"
#include "env/home_dir.h"
#include "feature/theme.h"

Shell::Shell()
    : exit_check(false)
{
    variable_manager.set("PWD", std::filesystem::current_path().lexically_normal().string())
                    .set("USER", user_name)
                    .set("HOME_DIR", home_dir)
                    .set("COLOR_THEME", theme_default.at("theme_name"))
                    .set("COLOR_NAME", theme_default.at("name"))
                    .set("COLOR_PATH", theme_default.at("path"))
                    .set("COLOR_DIR", theme_default.at("dir"))
                    .set("COLOR_WARN", theme_default.at("warn"))
                    .set("COLOR_SAVE", theme_default.at("save"))
                    .set("COLOR_RESET", theme_default.at("reset"))
                    .set("SYSTEM", sys);
}

int Shell::run(std::istream& in, std::ostream& out, std::ostream& err) {
    StreamManager stream_manager(in, out, err);

    int runtime_status = 0;
    while (!exit_check) {
        if(stream_manager.in().eof()){
            break;
        }
        stream_manager.out() << "\n\n" << variable_manager.get("COLOR_NAME") << variable_manager.get("USER") << variable_manager.get("COLOR_RESET")
                             << ' ' << variable_manager.get("COLOR_PATH") << variable_manager.get("PWD") << variable_manager.get("COLOR_RESET") << '\n';
        if (runtime_status != 0) {
            stream_manager.out() << variable_manager.get("COLOR_WARN");
        }
        // stream_manager.out() << runtime_status;
        stream_manager.out() << "> " << variable_manager.get("COLOR_RESET");

        std::string input;
        std::getline(stream_manager.in(), input);

        runtime_status = run_command(parse_command(input), stream_manager);

        std::filesystem::current_path(std::filesystem::path(variable_manager.get("PWD")));
    }
    return runtime_status;
}

std::vector<std::string> Shell::parse_command(std::string_view input) {
    std::vector<std::string> arg;
    for (std::size_t i = 0; i < input.size();) {
        auto space = input.find(' ', i);
        if (space == std::string::npos) {
            space = input.size();
        }
        arg.push_back(std::string(input.substr(i, space)));
        i = space + 1;
    }
    return arg;
}

int Shell::run_command(const std::vector<std::string>& arg, StreamManager& stream_manager) {
    using namespace cmd;

    std::string_view command = arg[0];

    if (command == "alias") {
        return alias(arg, stream_manager, variable_manager);
    } else if (command == "cat") {
        return cat(arg, stream_manager, variable_manager);
    } else if (command == "cd") {
        return cd(arg, stream_manager, variable_manager);
    } else if (command == "clear") {
        return clear(arg, stream_manager, variable_manager);
    } else if (command == "date") {
        return date(arg, stream_manager, variable_manager);
    } else if (command == "echo") {
        return echo(arg, stream_manager, variable_manager);
    } else if (command == "exit") {
        return exit(arg, stream_manager, variable_manager);
    } else if (command == "help") {
        return help(arg, stream_manager, variable_manager);
    } else if (command == "la") {
        return la(arg, stream_manager, variable_manager);
    } else if (command == "ls") {
        return ls(arg, stream_manager, variable_manager);
    } else if (command == "mkdir") {
        return mkdir(arg, stream_manager, variable_manager);
    } else if (command == "pwd") {
        return pwd(arg, stream_manager, variable_manager);
    } else if (command == "rm") {
        return rm(arg, stream_manager, variable_manager);
    } else if (command == "time") {
        return time(arg, stream_manager, variable_manager);
    } else if (command == "touch") {
        return touch(arg, stream_manager, variable_manager);
    } else if (command == "whoami") {
        return whoami(arg, stream_manager, variable_manager);
    } else if (command == "yush") {
        return yush(arg, stream_manager, variable_manager);
    } else {
        stream_manager.err() << "command `" << command << "` not found.";
        return 127;
    }
}

int Shell::exit(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager) {
    exit_check = true;
    return 0;
}