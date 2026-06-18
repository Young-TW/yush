#pragma once

#include <filesystem>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <string_view>
#include <vector>

#include "cxxopts.hpp"

#include "command.h"
#include "history.h"
#include "env/system_var.h"
#include "variable_manager.h"

class Shell {
public:
    Shell();
    int run(cxxopts::ParseResult& result);
    int run(const std::filesystem::path& file);
    int exec_cmd(const Command& cmd);

    // Execute one input line, which may contain several commands joined by
    // `;`, `&&` or `||`. Returns the status of the last command run.
    int exec_line(const std::string& line);

    VariableManager vars;
    VariableManager functions;

private:
    std::ifstream fin;
    std::ofstream fout;
    int output();
    std::string read();
    std::string read(std::istream& input_stream);
    std::vector<Command> read_script(const std::filesystem::path& file);
    int exec_file(const Command& cmd);
    int exec_shell_builtin(const Command& cmd);

    int runtime_status = 0;
    bool exiting = false;
    int exit_code = 0;

    History history;
    const std::filesystem::path rc_file = ".config/yush/config.yush";
    const std::filesystem::path config_dir = ".config/yush";

    int cmd_alias(const std::vector<std::string>& arg);
    int cmd_cd(const std::vector<std::string>& arg);
    int cmd_echo(const std::vector<std::string>& arg);
    int cmd_export(const std::vector<std::string>& arg);
    int cmd_function(const std::vector<std::string>& arg);
    int cmd_if(const std::vector<std::string>& arg);
    int cmd_ls(const std::vector<std::string>& arg);
    int cmd_pwd(const std::vector<std::string>& arg);
    int cmd_set(const std::vector<std::string>& arg);
};
