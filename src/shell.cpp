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
#include <fmt/color.h>

#include "feature/path_str_gen.h"
#include "feature/string_parser.h"
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

    if (vars.get("HOME").empty()) {
        fmt::print(stderr, "Error: HOME is not set\n");
        exit(FAILURE);
    }

    this->rc_file = reverse_path_str_gen(vars.get("HOME"), "~/.config/yush/config.yush");
    this->history_file = reverse_path_str_gen(vars.get("HOME"), "~/.config/yush/history");
    this->config_dir = reverse_path_str_gen(vars.get("HOME"), "~/.config/yush");

    if (!(std::filesystem::exists(this->config_dir) && std::filesystem::is_directory(this->config_dir))) {
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
        fin.open(this->history_file);
        std::string input;
        while (!fin.eof()) {
            getline(fin, input);
            this->cmd_history.push_back(input);
        }

        fin.close();
    }
}

int Shell::run(cxxopts::ParseResult& result) {
    std::string input;

    if (result.count("command")) {
        std::string input = result["command"].as<std::string>();
        std::vector<std::string> arg = process_cmd(input);
        return exec_cmd(arg);
    }

    if (signal(SIGINT, SIG_IGN) == SIG_ERR) {
        fmt::print(stderr, "Error: signal handler failed\n");
        return FAILURE;
    }

    fout.open(this->history_file, std::ios::app);

    do {
        if (result["interactive"].as<bool>()) {
            this->output();
            input = this->read();
        }

        std::vector<std::string> arg = process_cmd(input);

        if (arg.empty()) {
            continue;
        }

        if (arg[0] == "exit") {
            if (arg.size() > 1) {
                return atoi(arg[1].c_str());
            }
            break;
        }

        runtime_status = exec_cmd(arg);
        if (!input.empty()) {
            fout << input << std::endl;
        }

    } while (!std::cin.eof());

    return runtime_status;
}

int Shell::run(const std::filesystem::path& file) {
    if (!std::filesystem::exists(file)) {
        fmt::print(stderr, "Error: script file `{}` not found\n", file.string());
        return FAILURE;
    }

    fin.open(file);
    std::string input;
    while (!fin.eof()) {
        input = this->read(fin);
        std::vector<std::string> arg = process_cmd(input);
        runtime_status = exec_cmd(arg);
    }

    fin.close();
    return runtime_status;
}

int Shell::output() {
    fmt::print(fg(fmt::color::orange),"\n{}", vars.get("USER"));
    fmt::print("@");
    fmt::print(fg(fmt::color::cyan),"{} ", vars.get("NAME"));
    fmt::print(fg(fmt::color::violet),"{}\n", path_str_gen(vars.get("HOME")));

    if (runtime_status != SUCCESS) {
        fmt::print(fg(fmt::color::red),"{} > ", runtime_status);
        return runtime_status;
    }

    fmt::print("> ");
    return SUCCESS;
}

std::string Shell::read() {
    std::string input;
    struct termios old_termios, new_termios;
    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    int current;
    int curser_index = 0;
    int history_index = this->cmd_history.size();
    while (1) {
        current = std::cin.get();
        if (current == 27) {
            int key1 = std::cin.get();
            int key2 = std::cin.get();
            if (key1 == '[') {
                switch (key2) {
                    case 'A':
                        if (history_index > 0) {
                            history_index--;
                            for (int i=0; i<input.size(); i++) {
                                fmt::print("\b \b");
                            }

                            input = this->cmd_history[history_index];
                            fmt::print("{}", input);
                            curser_index = input.size();
                        }

                        break;
                    case 'B':
                        if (history_index < this->cmd_history.size()) {
                            history_index++;
                            if (history_index == this->cmd_history.size()) {
                                for (int i=0; i<input.size(); i++) {
                                    fmt::print("\b \b");
                                }

                                input.clear();
                            } else {
                                for (int i=0; i<input.size(); i++) {
                                    fmt::print("\b \b");
                                }

                                input = this->cmd_history[history_index];
                            }

                            curser_index = input.size();
                            fmt::print("{}", input);
                        }

                        break;
                    case 'C':
                        if (curser_index < input.size()) {
                            fmt::print("\033[C");
                            curser_index++;
                        }

                        break;
                    case 'D':
                        if (curser_index > 0) {
                            fmt::print("\033[D");
                            curser_index--;
                        }

                        break;
                    default:
                        break;
                }
            }
        } else if ((current == 8 || current == 127) && curser_index > 0) {
            input.erase(curser_index - 1, 1);
            fmt::print("\b \b");
            curser_index--;
            int old_input_size = input.size() + 1;
            for (int i = curser_index; i < input.size(); i++) {
                fmt::print("{}", input[i]);
            }

            for (int i = input.size(); i < old_input_size; i++) {
                fmt::print(" ");
            }

            for (int i = curser_index; i < old_input_size; i++) {
                fmt::print("\033[D");
            }
        } else if (current == 10) {
            fmt::print("\n");
            break;
        } else {
            input += static_cast<char>(current);
            curser_index++;
            fmt::print("{}", static_cast<char>(current));
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
    return input;
}

std::string Shell::read(std::istream& input_stream) {
    std::string input;
    std::getline(input_stream, input);
    if (input[input.length()-1] == '\\') {
        input += read(input_stream);
    }

    return input;
}

std::vector<std::string> Shell::process_cmd(const std::string& cmd) {
    if (this->alias.exist(cmd)) {
        std::string alias_cmd(this->alias.get(cmd));
        return process_cmd(alias_cmd);
    }

    std::vector<std::string> result;
    std::size_t begin = std::string::npos;

    for (std::size_t i = 0; i < cmd.size(); i++) {
        if (cmd[i] == ' ') {
            if (begin != std::string::npos) {
                result.push_back(cmd.substr(begin, i - begin));
                begin = std::string::npos;
            }

            continue;
        }

        if (cmd[i] == '$') {
            if (begin != std::string::npos) {
                result.push_back(cmd.substr(begin, i - begin));
                begin = std::string::npos;
            }

            std::size_t end = cmd.find_first_not_of(
                "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_",
                i + 1);

            if (end == std::string::npos) {
                end = cmd.size();
            }

            std::string var_name = cmd.substr(i + 1, end - i - 1);
            result.emplace_back(vars.get(var_name));
            i = end - 1;
            continue;
        }

        if (cmd[i] == '"') {
            if (begin == std::string::npos || begin == i - 1) {
                continue;
            }

            if (begin != std::string::npos) {
                result.push_back(cmd.substr(begin, i - begin));
                begin = std::string::npos;
            }

            std::size_t end = cmd.find_first_of('"', i + 1);

            if (end == std::string::npos) {
                end = cmd.size();
            }

            result.emplace_back(cmd.substr(i + 1, end - i - 1));
            i = end;

            continue;
        }

        if (cmd[i] == '\'') {
            if (begin == std::string::npos || begin == i - 1) {
                std::size_t end = cmd.find_first_of('\'', i + 1);

                if (end == std::string::npos) {
                    end = cmd.size();
                }

                result.emplace_back(cmd.substr(i + 1, end - i - 1));
                i = end;

                continue;
            }

            if (begin != std::string::npos) {
                result.push_back(cmd.substr(begin, i - begin));
                begin = std::string::npos;
            }
        }

        if (cmd[i] == '#') {
            break;
        }

        if (begin == std::string::npos) {
            begin = i;
        }
    }

    if (begin != std::string::npos) {
        result.push_back(cmd.substr(begin));
    }

    return result;
}

int Shell::exec_shell_builtin(const std::vector<std::string>& arg) {
    using CommandType = int (Shell::*)(const std::vector<std::string>&);

    static const std::unordered_map<std::string, CommandType> command_map{
        {"alias", &Shell::cmd_alias},
        {"cd", &Shell::cmd_cd},
        {"echo", &Shell::cmd_echo},
        {"function", &Shell::cmd_function},
        {"if", &Shell::cmd_if},
        {"ls", &Shell::cmd_ls},
        {"pwd", &Shell::cmd_pwd},
        {"set", &Shell::cmd_set},
    };

    auto command_it = command_map.find(arg[0]);
    if (command_it != command_map.cend()) {
        return (this->*(command_it->second))(arg);
    }

    return NOT_FOUND;
}

int Shell::exec_cmd(std::vector<std::string>& arg) {
    if (arg.empty()) {
        return SUCCESS;
    }

    if (this->functions.exist(arg[0])) {
        for (const auto& cmd : string_parser(this->functions.get(arg[0]), '\n')) {
            std::vector<std::string> arg = process_cmd(cmd);
            runtime_status = exec_cmd(arg);
        }

        return runtime_status;
    }

    int shell_builtin_ans =
        exec_shell_builtin(arg);

    if (shell_builtin_ans != NOT_FOUND) {
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
        fmt::print(stderr, "Error: command `{}` not found.\n", arg[0]);
        return NOT_FOUND;
    }

    pid_t pid = fork();

    if (pid == PID_FAILURE) {
        return PID_FAILURE;
    }

    if (pid > 0) {
        int status;
        waitpid(pid, &status, SUCCESS);
        return status;
    }

    signal(SIGINT, SIG_DFL);

    execve(cmd_path_str.c_str(), argv.get(), environ);
    unreachable();
}
