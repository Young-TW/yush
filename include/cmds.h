#ifndef CMDS_H
#define CMDS_H

#include <filesystem>
#include <map>
#include <string>
#include <string_view>
#include <vector>

#include "stream_manager.hpp"
#include "variable_manager.h"

namespace cmds {
int alias(const std::vector<std::string>& arg, StreamManager& stream_manager,
          VariableManager& variable_manager);
int cat(const std::vector<std::string>& arg, StreamManager& stream_manager,
        VariableManager& variable_manager);
int cd(const std::vector<std::string>& arg, StreamManager& stream_manager,
       VariableManager& variable_manager);
int clear(const std::vector<std::string>& arg, StreamManager& stream_manager,
          VariableManager& variable_manager);
int cp(const std::vector<std::string>& arg, StreamManager& stream_manager,
       VariableManager& variable_manager);
int date(const std::vector<std::string>& arg, StreamManager& stream_manager,
         VariableManager& variable_manager);
int echo(const std::vector<std::string>& arg, StreamManager& stream_manager,
         VariableManager& variable_manager);
int function(const std::vector<std::string>& arg, StreamManager& stream_manager,
             VariableManager& variable_manager);
int help(const std::vector<std::string>& arg, StreamManager& stream_manager,
         VariableManager& variable_manager);
int ls(const std::vector<std::string>& arg, StreamManager& stream_manager,
       VariableManager& variable_manager);
int la(const std::vector<std::string>& arg, StreamManager& stream_manager,
       VariableManager& variable_manager);
int mkdir(const std::vector<std::string>& arg, StreamManager& stream_manager,
          VariableManager& variable_manager);
int mv(const std::vector<std::string>& arg, StreamManager& stream_manager,
       VariableManager& variable_manager);
int pwd(const std::vector<std::string>& arg, StreamManager& stream_manager,
        VariableManager& variable_manager);
int rm(const std::vector<std::string>& arg, StreamManager& stream_manager,
       VariableManager& variable_manager);
int set(const std::vector<std::string>& arg, StreamManager& stream_manager,
        VariableManager& variable_manager);
int touch(const std::vector<std::string>& arg, StreamManager& stream_manager,
          VariableManager& variable_manager);
int whoami(const std::vector<std::string>& arg, StreamManager& stream_manager,
           VariableManager& variable_manager);
int yush(const std::vector<std::string>& arg, StreamManager& stream_manager,
         VariableManager& variable_manager);
}  // namespace cmds

#endif
