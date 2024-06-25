#include "command.h"

#include <fmt/format.h>
#include <signal.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>

#include <filesystem>
#include <iostream>
#include <string>

#include "common.hpp"
#include "feature/string_parser.h"
#include "shell.h"

extern char** environ;

Command::Command() {}

Command::Command(std::string_view cmd) { this->command = cmd; }

int Command::assign(std::string_view cmd) {
    this->command = cmd;
    return 0;
}

int Command::assign(std::vector<std::string>& args) {
    this->args = args;
    return 0;
}

int Command::assign(Command& cmd) {
    this->command = cmd.command;
    this->args = cmd.args;
    return 0;
}

std::string Command::get() { return this->command; }

int Command::parse() {
    if (shell.functions.exist(this->command)) {
        Command alias_cmd = shell.functions.get(this->command);
        this->assign(alias_cmd);
        this->parse();
        return 0;
    }

    this->args.clear();
    std::size_t double_quote = std::string::npos;
    std::size_t single_quote = std::string::npos;
    std::size_t begin = std::string::npos;

    for (std::size_t i = 0; i < this->command.size(); i++) {
        if (this->command[i] == ' ') {
            if (begin != std::string::npos && double_quote == std::string::npos && single_quote == std::string::npos) {
                this->args.push_back(this->command.substr(begin, i - begin));
                begin = std::string::npos;
            }

            continue;
        }

        if (this->command[i] == '$') {
            if (begin != std::string::npos) {
                this->args.push_back(this->command.substr(begin, i - begin));
                begin = std::string::npos;
            }

            std::size_t end = this->command.find_first_not_of(
                "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
                "_",
                i + 1);

            if (end == std::string::npos) {
                end = this->command.size();
            }

            std::string var_name = this->command.substr(i + 1, end - i - 1);
            this->args.emplace_back(shell.vars.get(var_name));
            i = end - 1;
            continue;
        }

        if (this->command[i] == '"') {
            if (double_quote == std::string::npos) {
                double_quote = i;
                continue;
            }

            this->args.push_back(this->command.substr(double_quote + 1, i - double_quote - 1));
            begin = std::string::npos;
            double_quote = std::string::npos;
            continue;
        }

        if (this->command[i] == '\'') {
            if (single_quote == std::string::npos) {
                single_quote = i;
                continue;
            }

            this->args.push_back(this->command.substr(single_quote + 1, i - single_quote - 1));
            begin = std::string::npos;
            single_quote = std::string::npos;
            continue;
        }

        if (this->command[i] == '#') {
            break;
        }

        if (begin == std::string::npos) {
            begin = i;
        }
    }

    if (begin != std::string::npos) {
        this->args.push_back(this->command.substr(begin));
    }

    return 0;
}

bool Command::empty() { return this->command.empty(); }

const std::vector<std::string>& Command::arg() const { return this->args; }
