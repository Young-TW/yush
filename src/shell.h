#ifndef SHELL_H
#define SHELL_H

#include <string_view>
#include <vector>
#include <filesystem>
#include <string>

#include "feature/theme.h"
#include "env/system_var.h"
#include "commands/cmds.h"

class Shell {
public:
    explicit Shell();
    explicit Shell(std::istream& is);

    int run();

private:
    std::vector<std::string> parse_command(std::string_view input);
    int run_command(const std::vector<std::string>& arg, std::istream& is, std::ostream& os);
    int exit(const std::vector<std::string>& arg, std::istream& is, std::ostream& os, std::map<std::string, std::string>& variables);

    bool exit_check;
    std::istream& is;
    std::map<std::string, std::string> variables;
    std::map<std::string, std::string> current_theme;
};

#endif