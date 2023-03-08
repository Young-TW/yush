#include <iostream>
#include <string_view>
#include <fstream>
#include <unordered_map>

#include "stream_manager.hpp"
#include "shell.h"
#include "cmds.h"
#include "env/user.h"
#include "env/home_dir.h"
#include "feature/path_str_gen.h"
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

int Shell::run(std::istream& in, std::ostream& out, std::ostream& err, bool output) {
    StreamManager stream_manager(in, out, err);

    int runtime_status = 0;
    while (!exit_check && !stream_manager.in().eof()) {
        if (output) {
            stream_manager.out() << "\n\n"
                                 << variable_manager.get("COLOR_NAME") << variable_manager.get("USER")
                                 << variable_manager.get("COLOR_RESET") << ' '
                                 << variable_manager.get("COLOR_PATH") << path_str_gen(variable_manager.get("PWD"), variable_manager.get("HOME_DIR"))
                                 << variable_manager.get("COLOR_RESET") << '\n';
            if (runtime_status != 0) {
                stream_manager.out() << variable_manager.get("COLOR_WARN");
            }
            // stream_manager.out() << runtime_status; // when debug
            stream_manager.out() << "> " << variable_manager.get("COLOR_RESET");
        }

        std::string input;
        std::getline(stream_manager.in(), input);

        runtime_status = run_command(parse_command(input), stream_manager);

        std::filesystem::path current_path{variable_manager.get("PWD")};
        std::filesystem::current_path(current_path);
        variable_manager.set("PWD", current_path.lexically_normal().string());
    }
    return runtime_status;
}

std::vector<std::string> Shell::parse_command(std::string_view input) {
    std::vector<std::string> arg;
    for (std::size_t i = 0; i < input.size();) {
        std::size_t space = input.find(' ', i);
        if (space == std::string::npos) {
            space = input.size();
        }
        arg.emplace_back(input.substr(i, space-i));
        i = space + 1;
    }
    return arg;
}

int Shell::run_command(const std::vector<std::string>& arg, StreamManager& stream_manager) {
    using namespace cmd;

    static const std::unordered_map<std::string, decltype(&alias)> command_map = {
        {"alias", alias},
        {"cat", cat},
        {"cd", cd},
        {"clear", clear},
        {"date", date},
        {"echo", echo},
        {"help", help},
        {"la", la},
        {"ls", ls},
        {"mkdir", mkdir},
        {"pwd", pwd},
        {"rm", rm},
        {"set", set},
        {"touch", touch},
        {"whoami", whoami},
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

    stream_manager.err() << "command `" << arg[0] << "` not found.";
    return 127;
}
