#include "shell.h"

#include <iostream>
#include <string_view>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "feature/path_str_gen.h"
#include "feature/string_parser.h"
#include "feature/theme.h"
#include "feature/signal_handler.h"

extern char** environ;

Shell::Shell(std::istream& in, std::ostream& out, std::ostream& err)
    : stream(in, out, err) {
    vars.set("COLOR_THEME", theme_default.at("theme_name"))
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
        vars.set(key, value);
    }

    // const std::vector<std::string>& arg{
    //     std::filesystem::current_path().string(),
    //     std::string(vars.get("HOME_DIR")) + ".yushrc"};

    // Shell yushrc(stream.in(), stream.out(), stream.err());
    // yushrc.run(false);
}

int Shell::run(bool output) {
    std::string input;

    do {
        if (output) {
            this->output();
        }

        if (signal(SIGINT, signal_handler) == SIG_ERR) {
            stream.err() << "Error: signal handler failed\n";
        }

        std::getline(stream.in(), input);

        input = preprocess_cmd(input);
        std::vector<std::string> arg = string_parser(input, ' ');

        if (arg[0] == "exit") {
            if (arg.size() > 1) {
                return atoi(arg[1].c_str());
            }
            break;
        }

        runtime_status = exec_cmd(input, arg);
    } while (!stream.in().eof());

    return runtime_status;
}

// int Shell::exec_script(const std::filesystem::path& script_path) {
//     return 0;
// }

int Shell::output() {
    stream.out() << "\n"
                         << vars.get("COLOR_NAME")
                         << vars.get("USER") << "@"
                         << vars.get("NAME")
                         << vars.get("COLOR_RESET") << ' '
                         << vars.get("COLOR_PATH")
                         << path_str_gen(vars.get("HOME"))
                         << vars.get("COLOR_RESET") << '\n';
    if (runtime_status != 0) {
        stream.out() << vars.get("COLOR_WARN");
    }
    // stream.out() << runtime_status; // when debug
    stream.out() << "> " << vars.get("COLOR_RESET");
    return 0;
}

std::string Shell::preprocess_cmd(const std::string& cmd) {
    if (cmd.empty()) {
        return "";
    }

    size_t flag = 0;
    while (cmd[flag] == ' ') {
        flag++;
    }

    std::string ans;
    for (size_t i = flag; i < cmd.size(); i++) {
        if (cmd[i] == ' ') {
            if (i + 1 < cmd.size() && cmd[i + 1] == ' ') {
                continue;
            }
        }
        ans += cmd[i];
    }

    return ans;
}

int Shell::exec_shell_builtin(const std::vector<std::string>& arg) {
    using namespace cmds;
    static const std::unordered_map<std::string, decltype(&alias)> command_map{
        {"alias", alias}, {"cat", cat},
        {"cd", cd},       {"clear", clear},
        {"cp", cp},       {"date", date},
        {"echo", echo},   {"function", function},
        {"la", la},       {"ls", ls},
        {"mkdir", mkdir}, {"mv", mv},
        {"pwd", pwd},     {"rm", rm},
        {"set", set},     {"touch", touch},
        {"whoami", whoami},
    };

    auto command_it = command_map.find(arg[0]);
    if (command_it != command_map.cend()) {
        return command_it->second(arg, stream, vars);
    }

    return 127;
}

int Shell::exec_cmd(const std::string current_command,
             std::vector<std::string>& arg) {
    if (current_command.empty()) {
        return 0;
    }

    int shell_builtin_ans =
        exec_shell_builtin(arg);

    if (shell_builtin_ans != 127) {
        return shell_builtin_ans;
    }

    std::vector<std::string> cmd_paths =
        string_parser(vars.get("PATH"), ':');

    for (const auto& cmd : cmd_paths) {
        std::filesystem::path cmd_path = cmd / std::filesystem::path(arg[0]);

        if (std::filesystem::exists(cmd_path) &&
            std::filesystem::is_regular_file(cmd_path)) {
            std::unique_ptr<char *[]> argv = std::make_unique<char *[]>(arg.size() + 1);
            std::string cmd_path_str = cmd_path.lexically_normal().string();
            argv[0] = cmd_path_str.data();
            for (size_t i = 1; i < arg.size(); i++) {
                argv[i] = arg[i].data();
            }

            return execve(argv[0], argv.get(), environ);
        }
    }

    stream.err() << "command `" << arg[0] << "` not found.\n";

    return 127;
}
