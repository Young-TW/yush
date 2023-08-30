#ifndef SHELL_H
#define SHELL_H

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

#include <cxxopts.hpp>

#include "env/system_var.h"
#include "variable_manager.h"

class Shell {
    public:
        Shell();
        int run(cxxopts::ParseResult& result);

    private:
        int output();
        int exec_cmd(std::vector<std::string>& arg);
        int exec_shell_builtin(const std::vector<std::string>& arg);
        std::vector<std::string> process_cmd(const std::string& cmd);

        int runtime_status = 0;
        VariableManager vars;

        static int cmd_alias(const std::vector<std::string>& arg,VariableManager& vars);
        static int cmd_cd(const std::vector<std::string>& arg,VariableManager& vars);
        static int cmd_clear(const std::vector<std::string>& arg,VariableManager& vars);
        static int cmd_echo(const std::vector<std::string>& arg,VariableManager& vars);
        static int cmd_function(const std::vector<std::string>& arg,VariableManager& vars);
        static int cmd_ls(const std::vector<std::string>& arg,VariableManager& vars);
        static int cmd_pwd(const std::vector<std::string>& arg,VariableManager& vars);
        static int cmd_set(const std::vector<std::string>& arg,VariableManager& vars);

};

#endif
