#ifndef SHELL_H
#define SHELL_H

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>
#include <fstream>

#include <cxxopts.hpp>

#include "env/system_var.h"
#include "variable_manager.h"

class Shell {
    public:
        Shell();
        int run(cxxopts::ParseResult& result);
        int run(const std::filesystem::path& file);

    private:
        std::ifstream fin;
        std::ofstream fout;
        int output();
        std::string read();
        int exec_cmd(std::vector<std::string>& arg);
        int exec_shell_builtin(const std::vector<std::string>& arg);
        std::vector<std::string> process_cmd(const std::string& cmd);

        int runtime_status = 0;
        enum return_value {
            PID_FAILURE = -1,
            SUCCESS = 0,
            FAILURE = 1,
            EXIT = 2,
            NOT_FOUND = 127,
        };

        std::vector<std::string> cmd_history;
        std::filesystem::path rc_file;
        std::filesystem::path history_file;
        std::filesystem::path config_dir;

        VariableManager vars;
        VariableManager alias;
        VariableManager functions;

        int cmd_alias(const std::vector<std::string>& arg);
        int cmd_cd(const std::vector<std::string>& arg);
        int cmd_echo(const std::vector<std::string>& arg);
        int cmd_function(const std::vector<std::string>& arg);
        int cmd_if(const std::vector<std::string>& arg);
        int cmd_ls(const std::vector<std::string>& arg);
        int cmd_pwd(const std::vector<std::string>& arg);
        int cmd_set(const std::vector<std::string>& arg);
};

#endif
