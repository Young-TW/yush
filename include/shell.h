#ifndef SHELL_H
#define SHELL_H

#include <cxxopts.hpp>
#include <filesystem>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <string_view>
#include <vector>

#include "command.h"
#include "env/system_var.h"
#include "variable_manager.h"

class Shell {
public:
    Shell();
    int run(cxxopts::ParseResult& result);
    int run(const std::filesystem::path& file);

    VariableManager vars;
    std::map<std::string, Command> alias;
    VariableManager functions;

private:
    std::ifstream fin;
    std::ofstream fout;
    int output();
    std::string read();
    std::string read(std::istream& input_stream);
    int exec_shell_builtin(const std::vector<std::string>& arg);
    int read_history();
    int write_history(const std::string& cmd);

    int runtime_status = 0;

    std::vector<std::string> cmd_history;
    std::filesystem::path rc_file;
    std::filesystem::path history_file;
    std::filesystem::path config_dir;

    int cmd_alias(const std::vector<std::string>& arg);
    int cmd_cd(const std::vector<std::string>& arg);
    int cmd_echo(const std::vector<std::string>& arg);
    int cmd_function(const std::vector<std::string>& arg);
    int cmd_if(const std::vector<std::string>& arg);
    int cmd_ls(const std::vector<std::string>& arg);
    int cmd_pwd(const std::vector<std::string>& arg);
    int cmd_set(const std::vector<std::string>& arg);

    friend class Command;
};

static Shell shell;

#endif
