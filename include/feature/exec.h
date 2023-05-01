#ifndef FEATURE_EXEC_H
#define FEATURE_EXEC_H

#include <vector>
#include <string>

#include "variable_manager.h"
#include "stream_manager.hpp"
#include "cmds.h"

int exec_shell_builtin(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager);

int exec_cmd(const std::string current_command, const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager);

#endif