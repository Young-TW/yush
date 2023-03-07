#ifndef CMDS_H
#define CMDS_H

#include <string>
#include <string_view>
#include <vector>
#include <map>
#include <filesystem>

#include "stream_manager.hpp"
#include "variable_manager.h"

namespace cmd {
    int alias(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager);
    int cat(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager);
    int cd(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager);
    int clear(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager);
    int date(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager);
    int echo(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager);
    int exit(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager);
    int help(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager);
    int ls(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager);
    int la(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager);
    int mkdir(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager);
    int pwd(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager);
    int rm(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager);
    int time(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager);
    int touch(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager);
    int whoami(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager);
    int yush(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager);
}

#endif