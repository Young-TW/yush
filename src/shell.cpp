#include "shell.h"

#include <iostream>
#include <string_view>
#include <unistd.h>
#include "feature/exec.h"
#include "feature/path_str_gen.h"
#include "feature/preprocess_cmd.h"
#include "feature/string_parser.h"
#include "feature/theme.h"

Shell::Shell(std::istream& in, std::ostream& out, std::ostream& err)
    : stream_manager(in, out, err) {
    variable_manager.set("COLOR_THEME", theme_default.at("theme_name"))
        .set("COLOR_NAME", theme_default.at("name"))
        .set("COLOR_PATH", theme_default.at("path"))
        .set("COLOR_DIR", theme_default.at("dir"))
        .set("COLOR_WARN", theme_default.at("warn"))
        .set("COLOR_SAVE", theme_default.at("save"))
        .set("COLOR_RESET", theme_default.at("reset"))
        .set("SYSTEM", sys)
        .set("SHELL", "yush");

    for (char** current = environ; *current; current++) {
        std::string current_str(*current);
        auto delimiter = current_str.find('=');
        std::string key(current_str.substr(0, delimiter));
        std::string value(
            delimiter != std::string::npos ?
            current_str.substr(delimiter + 1) :
            "");
        variable_manager.set(key, value);
    }

    const std::vector<std::string>& arg{
        std::filesystem::current_path().string(),
        std::string(variable_manager.get("HOME_DIR")) + ".yushrc"};

    cmds::yush(arg, stream_manager, variable_manager);
}

int Shell::run(bool output) {
    std::string input;
    do {
        if (output) {
            this->output();
        }

        std::getline(stream_manager.in(), input);

        input = preprocess_cmd(input);
        std::vector<std::string> arg = string_parser(input, ' ');

        if (arg[0] == "exit") {
            if (arg.size() > 1) {
                return atoi(arg[1].c_str());
            }
            break;
        }

        runtime_status = exec_cmd(input, arg, stream_manager, variable_manager);
    } while (!stream_manager.in().eof());

    return runtime_status;
}

int Shell::output() {
    stream_manager.out() << "\n"
                         << variable_manager.get("COLOR_NAME")
                         << variable_manager.get("USER") << "@"
                         << variable_manager.get("NAME")
                         << variable_manager.get("COLOR_RESET") << ' '
                         << variable_manager.get("COLOR_PATH")
                         << path_str_gen(variable_manager.get("HOME"))
                         << variable_manager.get("COLOR_RESET") << '\n';
    if (runtime_status != 0) {
        stream_manager.out() << variable_manager.get("COLOR_WARN");
    }
    // stream_manager.out() << runtime_status; // when debug
    stream_manager.out() << "> " << variable_manager.get("COLOR_RESET");
    return 0;
}
