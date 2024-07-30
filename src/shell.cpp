#include "shell.h"

#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>

#include <iostream>

#include "cxxopts.hpp"
#include "fmt/color.h"
#include "fmt/format.h"

#include "common.hpp"
#include "feature/path_str_gen.h"
#include "feature/string_parser.h"

extern char** environ;

Shell::Shell() {
    vars.set("SYSTEM", sys).set("SHELL", "yush");

    for (char** current = environ; *current; current++) {
        std::string current_str(*current);
        auto delimiter = current_str.find('=');
        std::string key(current_str.substr(0, delimiter));
        std::string value(delimiter != std::string::npos ? current_str.substr(delimiter + 1) : "");
        vars.set(key, value);
    }

    if (vars.get("HOME").empty()) {
        fmt::print(stderr, "Error: HOME is not set\n");
        exit(1);
    }

    this->rc_file = reverse_path_str_gen(vars.get("HOME"), "~/.config/yush/config.yush");
    this->history_file = reverse_path_str_gen(vars.get("HOME"), "~/.config/yush/history");
    this->config_dir = reverse_path_str_gen(vars.get("HOME"), "~/.config/yush");

    if (!(std::filesystem::exists(this->config_dir) &&
          std::filesystem::is_directory(this->config_dir))) {
        fmt::print(stderr, "Error: yush config dir path is not exists\n");
        fmt::print(stdout, "Auto creating config dir\n");
        std::filesystem::create_directory(config_dir);
    }

    if (std::filesystem::exists(this->rc_file)) {
        this->run(this->rc_file);
    }

    if (!std::filesystem::exists(this->history_file)) {
        fmt::print(stderr, "Error: history file path is empty\n");
        return;
    } else {
        this->read_history();
    }
}

int Shell::read_history() {
    fin.open(this->history_file);
    std::string input;
    while (!fin.eof()) {
        getline(fin, input);
        this->cmd_history.push_back(input);
    }

    fin.close();
    return 0;
}

int Shell::run(cxxopts::ParseResult& result) {
    Command command;

    if (signal(SIGINT, SIG_IGN) == SIG_ERR) {
        fmt::print(stderr, "Error: signal handler failed\n");
        return 1;
    }

    do {
        if (result["interactive"].as<bool>()) {
            this->output();
            command.assign(this->read());
        }

        command.parse();

        if (command.empty()) {
            continue;
        }

        if (command.arg()[0] == "exit") {
            if (command.arg().size() > 1) {
                return atoi(command.arg()[1].c_str());
            }
            break;
        }

        runtime_status = exec_cmd(command);
        if (!command.empty()) {
            this->write_history(command.get());
        }
    } while (!std::cin.eof());

    return runtime_status;
}

int Shell::write_history(const std::string& cmd) {
    fout.open(this->history_file, std::ios::app);
    fout << cmd << std::endl;
    fout.close();
    return 0;
}

int Shell::run(const std::filesystem::path& file) {
    std::vector<Command> commands = read_script(file);
    for (auto& command : commands) {
        if (!command.empty()) {
            command.parse();
            shell.runtime_status = exec_cmd(command);
            this->write_history(command.get());
        }
    }

    return runtime_status;
}

std::vector<Command> Shell::read_script(const std::filesystem::path& file) {
    if (!std::filesystem::exists(file)) {
        fmt::print(stderr, "Error: script file `{}` not found\n", file.string());
        return {};
    }

    std::vector<Command> commands;
    std::ifstream fin(file);
    while (!fin.eof()) {
        commands.push_back(Command(shell.read(fin)));
    }

    fin.close();
    return commands;
}

int Shell::output() {
    fmt::print(fg(fmt::color::orange), "\n{}", vars.get("USER"));
    fmt::print("@");
    fmt::print(fg(fmt::color::cyan), "{} ", vars.get("NAME"));
    fmt::print(fg(fmt::color::violet), "{}\n", path_str_gen(vars.get("HOME")));

    if (runtime_status != 0) {
        fmt::print(fg(fmt::color::red), "{} > ", runtime_status);
        return runtime_status;
    }

    fmt::print("> ");
    return 0;
}

std::string Shell::read() {
    termios old_termios, new_termios;
    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
    std::string input;
    int current;
    std::size_t cursor_index = 0;
    std::size_t history_index = this->cmd_history.size();
    while (true) {
        current = std::cin.get();
        if (current == 27) {
            int key1 = std::cin.get();
            int key2 = std::cin.get();
            if (key1 == '[') {
                switch (key2) {
                    case 'A':
                        if (history_index > 0) {
                            history_index--;
                            for (std::size_t i = 0; i < input.size(); i++) {
                                fmt::print("\b \b");
                            }

                            input = this->cmd_history[history_index];
                            fmt::print("{}", input);
                            cursor_index = input.size();
                        }

                        break;
                    case 'B':
                        if (history_index < this->cmd_history.size()) {
                            history_index++;
                            if (history_index == this->cmd_history.size()) {
                                for (std::size_t i = 0; i < input.size(); i++) {
                                    fmt::print("\b \b");
                                }

                                input.clear();
                            } else {
                                for (std::size_t i = 0; i < input.size(); i++) {
                                    fmt::print("\b \b");
                                }

                                input = this->cmd_history[history_index];
                            }

                            cursor_index = input.size();
                            fmt::print("{}", input);
                        }

                        break;
                    case 'C':
                        if (cursor_index < input.size()) {
                            fmt::print("\033[C");
                            cursor_index++;
                        }

                        break;
                    case 'D':
                        if (cursor_index > 0) {
                            fmt::print("\033[D");
                            cursor_index--;
                        }

                        break;
                    default:
                        break;
                }
            }
        } else if ((current == 8 || current == 127)) {
            if (cursor_index > 0) {
                input.erase(cursor_index - 1, 1);
                fmt::print("\b \b");
                cursor_index--;
            }

            std::size_t old_input_size = input.size() + 1;
            for (std::size_t i = cursor_index; i < input.size(); i++) {
                fmt::print("{}", input[i]);
            }

            for (std::size_t i = input.size(); i < old_input_size; i++) {
                fmt::print(" ");
            }

            for (std::size_t i = cursor_index; i < old_input_size; i++) {
                fmt::print("\033[D");
            }
        } else if (current == 10) {
            fmt::print("\n");
            break;
        } else {
            input += static_cast<char>(current);
            cursor_index++;
            fmt::print("{}", static_cast<char>(current));
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
    return input;
}

std::string Shell::read(std::istream& input_stream) {
    std::string input;
    std::getline(input_stream, input);
    if (input[input.length() - 1] == '\\') {
        input += read(input_stream);
    }

    return input;
}

int Shell::exec_cmd(const Command& cmd) {
    int status;

    if (functions.exist(cmd.arg()[0])) {
        for (const auto& cmd_str : string_parser(functions.get(cmd.arg()[0]), '\n')) {
            Command command(cmd_str);
            status = exec_cmd(command);
        }
        return status;
    }

    status = exec_file(cmd);
    if (status != 127) {
        return status;
    }

    return exec_shell_builtin(cmd);
}

int Shell::exec_file(const Command& cmd) {
    std::unique_ptr<char*[]> argv = std::make_unique<char*[]>(cmd.arg().size() + 1);
    for (size_t i = 0; i < cmd.arg().size(); i++) {
        argv[i] = const_cast<char*>(cmd.arg()[i].c_str());
    }

    std::string file_path_str;
    if (std::filesystem::exists(cmd.arg()[0]) && std::filesystem::is_regular_file(cmd.arg()[0])) {
        file_path_str = cmd.arg()[0];
    } else {
        std::vector<std::string> paths = string_parser(shell.vars.get("PATH"), ':');
        for (const auto& path : paths) {
            std::filesystem::path file_path = path / std::filesystem::path(cmd.arg()[0]);
            if (std::filesystem::exists(file_path) && std::filesystem::is_regular_file(file_path)) {
                file_path_str = file_path.lexically_normal().string();
                break;
            }
        }
    }
    if (file_path_str.empty()) {
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
    execve(file_path_str.c_str(), argv.get(), environ);
    unreachable();
}

int Shell::exec_shell_builtin(const Command& cmd) {
    using CommandType = int (Shell::*)(const std::vector<std::string>&);

    static const std::unordered_map<std::string, CommandType> command_map{
        {"alias", &Shell::cmd_alias},       {"cd", &Shell::cmd_cd},   {"echo", &Shell::cmd_echo},
        {"function", &Shell::cmd_function}, {"if", &Shell::cmd_if},   {"ls", &Shell::cmd_ls},
        {"pwd", &Shell::cmd_pwd},           {"set", &Shell::cmd_set},
    };

    auto command_it = command_map.find(cmd.arg()[0]);
    if (command_it != command_map.cend()) {
        return (this->*(command_it->second))(cmd.arg());
    }

    return 127;
}
