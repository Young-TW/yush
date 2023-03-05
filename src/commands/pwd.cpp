#include <filesystem>

#include "stream_manager.hpp"
#include "variable_manager.h"
#include "commands/cmds.h"

int cmd::pwd(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager){
    stream_manager.out() << variable_manager.get("PWD");
    return 0;
}