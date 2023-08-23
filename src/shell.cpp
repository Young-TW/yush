#include "shell.h"

#include <iostream>
#include <fstream>
#include <string_view>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>

#include <sys/wait.h>

#include <cxxopts.hpp>

#include <fmt/format.h>

#include "feature/path_str_gen.h"
#include "feature/string_parser.h"
#include "feature/theme.h"
#include "feature/signal_handler.h"
#include "common.hpp"

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

    if (!std::filesystem::exists(arg[1])) {
        fmt::print(fg(fmt::color::red), "no rc file\n");
        return;
    }

    std::ifstream fin(arg[1]);

    std::string input;
    while (!fin.eof()) {
        getline(fin, input);
        std::vector<std::string> arg = process_cmd(input);
        runtime_status = exec_cmd(arg);
    }

    fin.close();
    std::filesystem::current_path(arg[0]);
}

int Shell::run(cxxopts::ParseResult& result) {
    std::string input;

    if (result.count("command")) {
        std::string input = result["command"].as<std::string>();
        std::vector<std::string> arg = process_cmd(input);
        return exec_cmd(arg);
    }

    if (result.count("script")) {
        if (result["script"].as<std::filesystem::path>().empty()) {
            std::cerr << "Error: script and interactive cannot be used at the same time\n";
            return 1;
        }

        std::ifstream fin(result["script"].as<std::filesystem::path>());
        while (!fin.eof()) {
            getline(fin, input);
            std::vector<std::string> arg = process_cmd(input);
            runtime_status = exec_cmd(arg);
        }

        fin.close();
        return runtime_status;
    }

    if (signal(SIGINT, SIG_IGN) == SIG_ERR) {
        std::cerr << "Error: signal handler failed\n";
        return 1;
    }

    do {
        if (result["interactive"].as<bool>()) {
            this->output();


            getline(std::cin, input);
        }

        std::vector<std::string> arg = process_cmd(input);

        if (arg[0] == "exit") {
            if (arg.size() > 1) {
                return atoi(arg[1].c_str());
            }
            break;
        }

        runtime_status = exec_cmd(arg);
    } while (!std::cin.eof());

    return runtime_status;
}

int Shell::output() {
    fmt::print(fg(fmt::color::orange),"\n{}", vars.get("USER"));
    fmt::print("@");
    fmt::print(fg(fmt::color::cyan),"{} ", vars.get("NAME"));
    fmt::print(fg(fmt::color::purple),"{}\n", path_str_gen(vars.get("HOME")));

    if (runtime_status != 0) {
        fmt::print(fg(fmt::color::red),"{} > ", runtime_status);
        return 0;
    }

    fmt::print("> ");
    return 0;
}

std::vector<std::string> Shell::process_cmd(const std::string& cmd) {
    if (cmd.empty() || cmd[0] == '#') {
        return {};
    }

    size_t flag = 0;
    while (cmd[flag] == ' ') {
        flag++;
        if (flag == cmd.size()) {
            return {};
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

    return string_parser(cmd, ' ');
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

int Shell::exec_cmd(std::vector<std::string>& arg) {
    if (arg.empty()) {
        return 0;
    }

    int shell_builtin_ans =
        exec_shell_builtin(arg);

    if (shell_builtin_ans != 127) {
        return shell_builtin_ans;
    }

    std::unique_ptr<char *[]> argv = std::make_unique<char *[]>(arg.size() + 1);
    for (size_t i = 0; i < arg.size(); i++) {
        argv[i] = arg[i].data();
    }

    std::string cmd_path_str;

    if (std::filesystem::exists(arg[0]) && std::filesystem::is_regular_file(arg[0])) {
        cmd_path_str = arg[0];
    } else {
        std::vector<std::string> cmd_paths =
            string_parser(vars.get("PATH"), ':');

        for (const auto& cmd : cmd_paths) {
            std::filesystem::path cmd_path = cmd / std::filesystem::path(arg[0]);

            if (std::filesystem::exists(cmd_path) &&
                std::filesystem::is_regular_file(cmd_path)) {
                cmd_path_str = cmd_path.lexically_normal().string();
                break;
            }
        }
    }

    if (cmd_path_str.empty()) {
        std::cerr << "command `" << arg[0] << "` not found.\n";
        return 127;
    }

    pid_t pid = fork();

    if (pid == -1) {
        return -1;
    }

    if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        return status;
    }

    signal(SIGINT, SIG_DFL);

    execve(cmd_path_str.c_str(), argv.get(), environ);
    unreachable();
}
