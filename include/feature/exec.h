#ifndef FEATURE_EXEC_H
#define FEATURE_EXEC_H

#include <string>
#include <vector>

#include "cmds.h"
#include "stream_manager.hpp"
#include "variable_manager.h"

int exec_shell_builtin(const std::vector<std::string>& arg,
                       StreamManager& stream_manager,
                       VariableManager& variable_manager);

int exec_cmd(const std::string current_command,
             const std::vector<std::string>& arg, StreamManager& stream_manager,
             VariableManager& variable_manager);

#endif
