#include "shell.h"

#include <pwd.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <string_view>
#include <unordered_map>

#include "cmds.h"
#include "feature/path_str_gen.h"
#include "feature/string_parser.h"
#include "feature/theme.h"
#include "stream_manager.hpp"

Shell::Shell(std::istream& in, std::ostream& out, std::ostream& err)
    : exit_check(false), stream_manager(in, out, err)
{
    variable_manager
        .set("USER", std::getenv("USER"))
        .set("HOME_DIR", getpwuid(getuid())->pw_dir)
        .set("COLOR_THEME", theme_default.at("theme_name"))
        .set("COLOR_NAME", theme_default.at("name"))
        .set("COLOR_PATH", theme_default.at("path"))
        .set("COLOR_DIR", theme_default.at("dir"))
        .set("COLOR_WARN", theme_default.at("warn"))
        .set("COLOR_SAVE", theme_default.at("save"))
        .set("COLOR_RESET", theme_default.at("reset"))
        .set("SYSTEM", sys)
        .set("PATH", std::getenv("PATH"))
        .set("0", "yush");

    const std::vector<std::string>& arg{
        std::filesystem::current_path().string(),
        std::string(variable_manager.get("HOME_DIR")) + ".yushrc"
    };

    cmds::yush(arg, stream_manager, variable_manager);
}

int Shell::run(bool output) {
    int runtime_status = 0;
    while (!exit_check && !stream_manager.in().eof()) {
        if (output) {
            stream_manager.out()
                << "\n"
                << variable_manager.get("COLOR_NAME")
                << variable_manager.get("USER")
                << variable_manager.get("COLOR_RESET") << ' '
                << variable_manager.get("COLOR_PATH")
                << path_str_gen(variable_manager.get("HOME_DIR"))
                << variable_manager.get("COLOR_RESET") << '\n';
            if (runtime_status != 0) {
                stream_manager.out() << variable_manager.get("COLOR_WARN");
            }
            // stream_manager.out() << runtime_status; // when debug
            stream_manager.out() << "> " << variable_manager.get("COLOR_RESET");
        }

        std::string input;
        std::getline(stream_manager.in(), input);

        runtime_status = run_command(input);
    }

    return runtime_status;
}

int Shell::cmd_call(std::vector<std::string>& arg) {
    std::vector<std::string> cmd_paths =
        string_parser(variable_manager.get("PATH"), ':');
    std::string current_command;
    for (const auto& x : arg) {
        current_command += ' ' + x;
    }
    for (const auto& cmd : cmd_paths) {
        std::filesystem::path cmd_path = cmd / std::filesystem::path(arg[0]);

        if (std::filesystem::exists(cmd_path) &&
            std::filesystem::is_regular_file(cmd_path)) {
            return std::system(current_command.c_str());
        }
    }
    stream_manager.err() << "command `" << arg[0] << "` not found.\n";
    return 127;
}

int Shell::run_command(const std::string& current_command) {
    using namespace cmds;

    if (current_command.empty()) {
        return 0;
    }

    std::vector<std::string> arg = string_parser(current_command, ' ');

    static const std::unordered_map<std::string, decltype(&alias)> command_map{
        {"alias", alias}, {"cat", cat},
        {"cd", cd},       {"clear", clear},
        {"cp", cp},       {"date", date},
        {"echo", echo},   {"function", function},
        {"help", help},   {"la", la},
        {"ls", ls},       {"mkdir", mkdir},
        {"mv", mv},       {"pwd", pwd},
        {"rm", rm},       {"set", set},
        {"touch", touch}, {"whoami", whoami},
        {"yush", yush},
    };

    if (arg[0] == "exit") {
        exit_check = true;
        return 0;
    }

    auto command_it = command_map.find(arg[0]);
    if (command_it != command_map.cend()) {
        return command_it->second(arg, stream_manager, variable_manager);
    }

    return cmd_call(arg);
    return 127;
}
