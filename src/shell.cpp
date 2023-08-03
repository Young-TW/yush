#include "shell.h"

#include <iostream>
#include <fstream>
#include <string_view>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include <fmt/format.h>

#include "feature/path_str_gen.h"
#include "feature/string_parser.h"
#include "feature/theme.h"
#include "feature/signal_handler.h"

extern char** environ;

Shell::Shell() {
    vars.set("SYSTEM", sys)
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

    const std::vector<std::string>& arg{
        std::filesystem::current_path().string(),
        std::string(vars.get("HOME")) + "/.yushrc"};

    std::ifstream fin;
    fin.open(arg[1]);
    while (!fin.eof()) {
        std::string input;
        getline(fin, input);
        input = preprocess_cmd(input);
        std::vector<std::string> arg = string_parser(input, ' ');
        exec_cmd(input, arg);
    }
    fin.close();

    std::filesystem::current_path(arg[0]);
}

int Shell::run(bool output) {
    std::string input;

    do {
        if (output) {
            this->output();
        }

        if (signal(SIGINT, signal_handler) == SIG_ERR) {
            std::cerr << "Error: signal handler failed\n";
        }

        getline(std::cin, input);

        input = preprocess_cmd(input);

        if (input.empty()) {
            continue;
        }

        std::vector<std::string> arg = string_parser(input, ' ');

        if (arg[0] == "exit") {
            if (arg.size() > 1) {
                return atoi(arg[1].c_str());
            }
            break;
        }

        runtime_status = exec_cmd(input, arg);
    } while (!std::cin.eof());

    return runtime_status;
}

int Shell::output() {
    fmt::print(fg(fmt::color::orange) | fmt::emphasis::blink,"\n{}", vars.get("USER"));
    fmt::print("@");
    fmt::print(fg(fmt::color::cyan) | fmt::emphasis::blink,"{} ", vars.get("NAME"));
    fmt::print(fg(fmt::color::purple) | fmt::emphasis::blink,"{}\n", path_str_gen(vars.get("HOME")));

    if (runtime_status != 0) {
        fmt::print(fg(fmt::color::red) | fmt::emphasis::blink,"{} > ", runtime_status);
        return 0;
    }

    fmt::print("> ");
    return 0;
}

std::string Shell::preprocess_cmd(const std::string& cmd) {
    if (cmd.empty()) {
        return "";
    }

    size_t flag = 0;
    while (cmd[flag] == ' ') {
        flag++;
        if (flag == cmd.size()) {
            return "";
        }
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
        {"alias", alias},       {"cd", cd},
        {"clear", clear},       {"echo", echo},
        {"function", function}, {"ls", ls},
        {"pwd", pwd},           {"set", set},
    };

    auto command_it = command_map.find(arg[0]);
    if (command_it != command_map.cend()) {
        return command_it->second(arg, vars);
    }

    return 127;
}

int Shell::exec_cmd(const std::string current_command, std::vector<std::string>& arg) {
    if (current_command.empty() || arg.empty()) {
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

    std::cerr << "command `" << arg[0] << "` not found.\n";

    return 127;
}
