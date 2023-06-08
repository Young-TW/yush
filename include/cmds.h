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
int alias(const std::vector<std::string>& arg, StreamManager& stream,
          VariableManager& vars);
int cat(const std::vector<std::string>& arg, StreamManager& stream,
        VariableManager& vars);
int cd(const std::vector<std::string>& arg, StreamManager& stream,
       VariableManager& vars);
int clear(const std::vector<std::string>& arg, StreamManager& stream,
          VariableManager& vars);
int cp(const std::vector<std::string>& arg, StreamManager& stream,
       VariableManager& vars);
int date(const std::vector<std::string>& arg, StreamManager& stream,
         VariableManager& vars);
int echo(const std::vector<std::string>& arg, StreamManager& stream,
         VariableManager& vars);
int function(const std::vector<std::string>& arg, StreamManager& stream,
             VariableManager& vars);
int ls(const std::vector<std::string>& arg, StreamManager& stream,
       VariableManager& vars);
int la(const std::vector<std::string>& arg, StreamManager& stream,
       VariableManager& vars);
int mkdir(const std::vector<std::string>& arg, StreamManager& stream,
          VariableManager& vars);
int mv(const std::vector<std::string>& arg, StreamManager& stream,
       VariableManager& vars);
int pwd(const std::vector<std::string>& arg, StreamManager& stream,
        VariableManager& vars);
int rm(const std::vector<std::string>& arg, StreamManager& stream,
       VariableManager& vars);
int set(const std::vector<std::string>& arg, StreamManager& stream,
        VariableManager& vars);
int touch(const std::vector<std::string>& arg, StreamManager& stream,
          VariableManager& vars);
int whoami(const std::vector<std::string>& arg, StreamManager& stream,
           VariableManager& vars);
}  // namespace cmds

#endif
