#include "shell.h"

#include <pwd.h>
#include <unistd.h>

#include <iostream>
#include <string_view>
#include <unordered_map>

#include "feature/path_str_gen.h"
#include "feature/string_parser.h"
#include "feature/theme.h"
#include "feature/exec.h"

Shell::Shell(std::istream& in, std::ostream& out, std::ostream& err)
    : stream_manager(in, out, err)
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
    std::string input;
    do {
        if (output) {
            this->output();
        }

        std::getline(stream_manager.in(), input);

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
    return 0;
}